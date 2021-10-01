/**
 * @file Stack.cpp
 */

#include "Stack.h"

bool StackPush(Stack_t* stackObject, StackElem_t value)
{
    VALIDATE(stackObject, StackValid, StackDump)

    if (stackObject->size == stackObject->capacity) {

        if (SecureRealloc(&stackObject->data, (stackObject->capacity * 2), sizeof (StackElem_t)))
            stackObject->capacity *= 2;
        else
            return false;

        for (size_t i = stackObject->size; i < stackObject->capacity; ++i) {
            stackObject->data[i] = (StackElem_t) POISON_VALUES::number;
        }
    }

    stackObject->size += 1;
    stackObject->data[stackObject->size - 1] = value;
    stackObject->top = value;

    *stackObject->stackHash = CalculateHash(stackObject->self, sizeof *stackObject);
    *stackObject->dataHash = CalculateHash(stackObject->data, sizeof (StackElem_t) * stackObject->capacity);

    VALIDATE(stackObject, StackValid, StackDump)

    return true;
}

bool StackPop(Stack_t* stackObject)
{
    VALIDATE(stackObject, StackValid, StackDump)

    stackObject->data[stackObject->size - 1] = (StackElem_t) POISON_VALUES::number;

    if (stackObject->size <= stackObject->capacity / 4) {

        if (SecureRealloc(&stackObject->data, (stackObject->capacity / 2), sizeof (StackElem_t)))
            stackObject->capacity /= 2;
        else
            return false;
    }

    stackObject->size -= 1;

    if (stackObject->size >= 1)
        stackObject->top = stackObject->data[stackObject->size - 1];
    else
        stackObject->top = (StackElem_t) 0;

    *stackObject->stackHash = CalculateHash(stackObject->self, sizeof *stackObject);
    *stackObject->dataHash = CalculateHash(stackObject->data, sizeof (StackElem_t) * stackObject->capacity);

    VALIDATE(stackObject, StackValid, StackDump)

    return true;
}

void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile, Location_t location)
{
    uint64_t minPtr = 1;

    for (int i = 0; i < 18; ++i)
        minPtr *= 2;

    assert(stackObject && localName && destFile && "Inapropriate pointer");
    assert((char*) stackObject->data > (char*) minPtr && "Inapropriate pointer");
    assert((char*) stackObject->dataHash > (char*) minPtr && "Inapropriate pointer");
    assert((char*) stackObject->stackHash > (char*) minPtr && "Inapropriate pointer");

//-------------------------------------STACK-DUMP----------------------------------------------------------------------------------------
    fprintf(destFile,
            "stack<uint64_t> [%p] (%s) \"%s\" from %s(%d), %s() \"%s\":\n"
            "\n"
            "\tsize_t      capacity    = %-16zd (%s)\n"
            "\tsize_t      size        = %-16zd (%s)\n"
            "\tStackElem_t top         = %-16llu (%s)\n"
            "\tHash_t*     stackHash   = %p (%s)\n"
            "\tHash_t      *stackHash  = %-16llu (%s)\n"
            "\tHash_t*     dataHash    = %p (%s)\n"
            "\tHash_t      *dataHash   = %-16llu (%s)\n"
            "\tStack_t*    CanaryLeft  = %p (%s)\n"
            "\tStack_t*    CanaryRight = %p (%s)\n"
            "\n"
            "\tdata<StackElem_t> [%p] (%s)\n"
            "\t{\n",

           stackObject->self, PointerValid(stackObject->self),                          stackObject->name, location.file,
           location.line, location.function,                                            localName, stackObject->capacity,
           SizeValid(stackObject->size, stackObject->capacity),                         stackObject->size,
           SizeValid(stackObject->size, stackObject->capacity),                         stackObject->top,
           NumberValid(stackObject->top),                                               stackObject->stackHash,
           PointerValid(stackObject->stackHash),                                        *stackObject->stackHash,
           HashValid(stackObject->self, sizeof *stackObject, *stackObject->stackHash),  stackObject->dataHash,
           PointerValid(stackObject->dataHash),                                         *stackObject->dataHash,
           HashValid(stackObject->data, sizeof (StackElem_t) * stackObject->capacity, *stackObject->dataHash),
           stackObject->canaryLeft, CanaryValid(stackObject, stackObject->canaryLeft),  stackObject->canaryRight,
           CanaryValid(stackObject, stackObject->canaryRight),                          stackObject->data, PointerValid(stackObject->data));
//---------------------------------------------------------------------------------------------------------------------------------------

    // dumping pushed data
    for (uint64_t i = 0; i < stackObject->size; ++i) {
        fprintf(destFile, "\t *[%llu] = %-5llu (%s)\n", i, stackObject->data[i], NumberValid(stackObject->data[i]));
    }

    // dumping poped/unused data
    for (uint64_t i = stackObject->size; i < stackObject->capacity; ++i) {
        fprintf(destFile, "\t [%llu] = %-5llu (%s)\n", i, stackObject->data[i], NumberValid(stackObject->data[i]));
    }

    fprintf(destFile, "\t}\n\n");
}

bool StackCtor(Stack_t* stackObject, const char* name)
{
    assert(stackObject && name && "Stack object initialization failed");

    // defining attributes
    stackObject->size = 0;
    stackObject->top  = 0;
    stackObject->name = name;
    stackObject->self = stackObject;

    if (SecureRealloc(&stackObject->data, 1, sizeof (StackElem_t)))
        stackObject->capacity = 1;
    else
        return false;

    stackObject->data[0] = 0;

    stackObject->canaryLeft  = stackObject->self;
    stackObject->canaryRight = stackObject->self;

    // defining methods
    stackObject->pop  = &StackPop;
    stackObject->push = &StackPush;
    stackObject->dump = &StackDump;

    // calculatig struct hash
    if (SecureRealloc(&stackObject->stackHash, 1, sizeof (Hash_t)) &&
        SecureRealloc(&stackObject->dataHash, 1, sizeof (Hash_t))) {
        *stackObject->stackHash = CalculateHash(stackObject->self, sizeof *stackObject);
        *stackObject->stackHash = CalculateHash(stackObject->data, sizeof (StackElem_t) * stackObject->capacity);
    }
    else
        return false;

    VALIDATE(stackObject, StackValid, StackDump)

    return true;
}

void StackDtor(Stack_t* stackObject)
{
    VALIDATE(stackObject, StackValid, StackDump)

    // Poisoning the values
    for (int i = 0; i < stackObject->size; ++i) {
        stackObject->data[i] = (StackElem_t) POISON_VALUES::number;
    }

    *stackObject->dataHash  = (Hash_t) POISON_VALUES::number;
    *stackObject->stackHash = (Hash_t) POISON_VALUES::number;

    // freeing allocated memory
    free(stackObject->data);
    free(stackObject->dataHash);
    free(stackObject->stackHash);

    // destroying methods
    stackObject->pop  = (bool (*)(stack*))                                 POISON_VALUES::pointer;
    stackObject->push = (bool (*)(stack*, StackElem_t))                    POISON_VALUES::pointer;
    stackObject->dump = (void (*)(stack*, const char*, FILE*, Location_t)) POISON_VALUES::pointer;

    //destroying attributes
    stackObject->name        = (char*)        POISON_VALUES::pointer;
    stackObject->data        = (StackElem_t*) POISON_VALUES::pointer;
    stackObject->stackHash   = (Hash_t*)      POISON_VALUES::pointer;
    stackObject->dataHash    = (Hash_t*)      POISON_VALUES::pointer;
    stackObject->self        = (Stack_t*)     POISON_VALUES::pointer;
    stackObject->canaryLeft  = (Stack_t*)     POISON_VALUES::pointer;
    stackObject->canaryRight = (Stack_t*)     POISON_VALUES::pointer;
    stackObject->size        = (size_t)       POISON_VALUES::number;
    stackObject->capacity    = (size_t)       POISON_VALUES::number;
    stackObject->top         = (StackElem_t)  POISON_VALUES::number;
}

bool StackNew(Stack_t** stackObject_ptr, const char* name)
{
    assert(stackObject_ptr && name && "Stack object initialization failed");

    *stackObject_ptr = (Stack_t*) calloc(1, sizeof (Stack_t));
    StackCtor(*stackObject_ptr, name);

    return true;
}

void StackDelete(Stack_t** stackObject_ptr)
{
    assert(stackObject_ptr && "Inapropriate pointer");

    StackDtor(*stackObject_ptr);
    free(*stackObject_ptr);
}

bool StackValid(Stack_t* stackObject)
{
    assert(stackObject && "Inapropriate pointer");

    bool validator = true;

    if (VALIDATION_DEPTH >= 1)
        validator = (strcmp(SizeValid(stackObject->size, stackObject->capacity), "ok") == 0  &&
                     IS_OK(Pointer, (void*) stackObject->data)       &&
                     IS_OK(Pointer, (void*) stackObject->self)       &&
                     IS_OK(Pointer, (void*) stackObject->pop)        &&
                     IS_OK(Pointer, (void*) stackObject->push)       &&
                     IS_OK(Pointer, (void*) stackObject->dump)       &&
                     IS_OK(Pointer, (void*) stackObject->name)       &&
                     IS_OK(Pointer, (void*) stackObject->stackHash)  &&
                     IS_OK(Number,  stackObject->top));

    if (!validator) return false;

    if (VALIDATION_DEPTH >= 2) {
        validator = (strcmp(CanaryValid(stackObject->self, stackObject->canaryLeft),  "ok") == 0 &&
                     strcmp(CanaryValid(stackObject->self, stackObject->canaryRight), "ok") == 0);
    }

    if (!validator) return false;

    if (VALIDATION_DEPTH >= 3) {

        for (int i = 0; i < stackObject->size; ++i) {
            validator = validator && IS_OK(Number, stackObject->data[i]);
        }

        validator = strcmp(HashValid(stackObject, sizeof *stackObject, *stackObject->stackHash), "ok") == 0;
    }

    return validator;
}

bool SecureRealloc(StackElem_t** buffer, size_t nElements, size_t elemSize)
{
    assert(buffer && "Inapropriate pointer");

    void* dataTmp = realloc(*buffer, nElements * elemSize);

    if (dataTmp)
        *buffer = (StackElem_t*) dataTmp;
    else
        return false;

    return true;
}

const char* NumberValid(StackElem_t value)
{
    if (value == (StackElem_t) POISON_VALUES::number)
        return "POISON!";

    return "ok";
}

const char* SizeValid(size_t size, size_t capacity)
{
    if (size > capacity || size < 0 || capacity < 0)
        return "ERROR!";

    return "ok";
}

const char* PointerValid(void* pointer)
{
    if (pointer == nullptr)
        return "ERROR!";
    else if (pointer == (void*) POISON_VALUES::pointer)
        return "POISON!";

    return "ok";
}

const char* HashValid(void* data, size_t dataSize, Hash_t hash)
{
    assert(data && "Inapropriate pointer");

    if (CalculateHash(data, dataSize) != hash)
        return "ERROR!";

    return "ok";
}

const char* CanaryValid(Stack_t* stackObject, Stack_t* canary)
{
    assert(canary && stackObject && "Inapropriate pointer");

    if (stackObject->self != canary)
        return "ERROR!";

    return "ok";
}
