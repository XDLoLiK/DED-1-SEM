/**
 * @file Stack.cpp
 */

#include "Stack.h"

bool StackPush(Stack_t* stackObject, StackElem_t value)
{
    VALIDATE(stackObject, StackValid, StackDump)

    if (stackObject->size == stackObject->capacity) {

        if (ReallocSuccess(&stackObject->data, (stackObject->capacity * 2), sizeof (StackElem_t)))
            stackObject->capacity *= 2;
        else
            return false;
    }

    stackObject->size += 1;
    stackObject->data[stackObject->size - 1] = value;
    stackObject->top = value;

    stackObject->hash = CalculateHash(stackObject->self, sizeof *stackObject);

    VALIDATE(stackObject, StackValid, StackDump)

    return true;
}

bool StackPop(Stack_t* stackObject)
{
    VALIDATE(stackObject, StackValid, StackDump)

    stackObject->data[stackObject->size - 1] = (StackElem_t) POISON_VALUES::number;

    if (stackObject->size <= stackObject->capacity / 4) {

        if (ReallocSuccess(&stackObject->data, (stackObject->capacity / 2), sizeof (StackElem_t)))
            stackObject->capacity /= 2;
        else
            return false;
    }

    stackObject->size -= 1;
    stackObject->top = stackObject->data[stackObject->size - 1];

    stackObject->hash = CalculateHash(stackObject->self, sizeof *stackObject);

    VALIDATE(stackObject, StackValid, StackDump)

    return true;
}

void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile)
{

}

bool StackCtor(Stack_t* stackObject, const char* name)
{
    assert(stackObject && name && "Stack object initialization failed");

    // defining attributes
    stackObject->size = 0;
    stackObject->name = name;
    stackObject->self = stackObject;
    stackObject->top = (StackElem_t) POISON_VALUES::number;

    if (ReallocSuccess(&stackObject->data, 1, sizeof (StackElem_t)))
        stackObject->capacity = 1;
    else
        return false;

    // defining methods
    stackObject->pop  = &StackPop;
    stackObject->push = &StackPush;
    stackObject->dump = &StackDump;

    stackObject->hash = CalculateHash(stackObject->self, sizeof *stackObject);

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

    // destroying methods
    stackObject->pop  = (bool (*)(stack*))                     POISON_VALUES::pointer;
    stackObject->push = (bool (*)(stack*, StackElem_t))        POISON_VALUES::pointer;
    stackObject->dump = (void (*)(stack*, const char*, FILE*)) POISON_VALUES::pointer;

    //destroying attributes
    stackObject->name     = (char*)        POISON_VALUES::pointer;
    stackObject->data     = (StackElem_t*) POISON_VALUES::pointer;
    stackObject->self     = (Stack_t*)     POISON_VALUES::pointer;
    stackObject->size     = (size_t)       POISON_VALUES::number;
    stackObject->capacity = (size_t)       POISON_VALUES::number;
    stackObject->top      = (StackElem_t)  POISON_VALUES::number;
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
    assert(stackObject_ptr);

    StackDtor(*stackObject_ptr);
    free(*stackObject_ptr);
}

bool StackValid(Stack_t* stackObject)
{
//    bool validator = true;
//    ...
//    if (VALIDATION_DEPTH == 1) {
//
//        return validator; /????????????????????????????
//    }

//    if (Validation.depth == 1) {
//
//    } else if (Validation.depth == 2) {
//
//    } else if (Validation.depth == 3) {
//
//    }

    return true;
}

bool ReallocSuccess(StackElem_t** buffer, size_t nElements, size_t elemSize)
{
    assert(buffer);

    void* dataTmp = realloc(*buffer, nElements * elemSize);

    if (dataTmp)
        *buffer = (StackElem_t*) dataTmp;
    else
        return false;

    return true;
}
