/**
 * @file Stack.cpp
 */

#include "Stack.h"

/// Deacrese and increase capacity coefficients
const size_t INCREMENT_COEFF = 2;
const size_t DECREMENT_COEFF = 2;

//{--------------------------------------------------------Capacity-change-functions-------------------------------------------------------

/**
 * The user shall not have access to these
 */

/**
 * Increases stack object's capacity if possible
 * @param stackObject pointer to the stack object
 * @return error code (or no error)
 */
ERROR_CODE IncreaseCapacity(Stack_t* stackObject);

/**
 * Decreases stack object's capacity if possible
 * @param stackObject pointer to the stack object
 * @return error code (or no error)
 */
ERROR_CODE DecreaseCapacity(Stack_t* stackObject);
//}----------------------------------------------------------------------------------------------------------------------------------------



//{--------------------------------------------------------STACK-METHODS-------------------------------------------------------------------

ERROR_CODE StackPush(Stack_t* stackObject, StackElem_t value) 
{

#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE


    if (stackObject->size == stackObject->capacity) {
        if (IncreaseCapacity(stackObject->self) != NO_ERROR)
            RETURN(CAPACITY_INCREMENT_ERROR);
    }

    stackObject->data[stackObject->size++] = value;


#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE


    RETURN(NO_ERROR);
}


ERROR_CODE StackPop(Stack_t* stackObject)
{

#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE


    if (stackObject->size <= 0) {
        RETURN(EMPTY_STACK_POP_ATTEMPT);
    }

    // a point when it's time to decrease the capacity
    size_t decrementPoint = stackObject->capacity / 4;

    if (stackObject->size <= decrementPoint) {
        if (DecreaseCapacity(stackObject->self) != NO_ERROR)
            RETURN(CAPACITY_DECREMENT_ERROR);
    }

    stackObject->data[--stackObject->size] = (StackElem_t) POISON_VALUES::NUMBER;


#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE


    RETURN(NO_ERROR);
}


StackElem_t StackTop(Stack_t* stackObject)
{

#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE


    if (stackObject->size <= 0) {
        RETURN(EMPTY_STACK_TOP_ATTEMPT);
    }

    return stackObject->data[stackObject->size - 1];
}


void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile, Location_t location)
{
    uint64_t minPtr = 1;

    for (int i = 0; i < 18; ++i)
        minPtr *= 2;

    assert(stackObject && localName && destFile && "Inapropriate pointer");
    assert((char*) stackObject->data > (char*) minPtr && "Inapropriate pointer");

//    int size_status = ...;
//    printf("%s", size_is_ok ? "da", "net");
}

//}-------------------------------------------------------------------------------------------------------------------------------


ERROR_CODE StackCtor(Stack_t* stackObject, const char* name)
{
    if (stackObject == nullptr || name == nullptr)
        return INITIALIZATION_ERROR;

    // defining attributes
    stackObject->size = 0;
    stackObject->name = name;
    stackObject->self = stackObject;

    if (SecureRealloc(&stackObject->data, 1, sizeof (StackElem_t)) == NO_ERROR)
        stackObject->capacity = 1;
    else
        return ALLOCATION_ERROR;

    stackObject->data[0] = 0;

    // setting up the canaries

    assert(&StackPop && &StackPush && &StackDump && &StackTop && "Invalid function pointer");

    // defining methods
    stackObject->pop  = &StackPop;
    stackObject->top  = &StackTop;
    stackObject->push = &StackPush;
    stackObject->dump = &StackDump;


#if defined(VALIDATION_ACTIVE)

    // calculatig struct hash !!!!!!!!!!!!

    stackObject->canaryLeft  = stackObject->self;
    stackObject->canaryRight = stackObject->self;

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE


    RETURN(NO_ERROR);
}

void StackDtor(Stack_t* stackObject)
{

#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

    stackObject->canaryLeft  = (Stack_t*)  POISON_VALUES::POINTER;
    stackObject->canaryRight = (Stack_t*)  POISON_VALUES::POINTER;
    stackObject->hash        = (Hash_t)    POISON_VALUES::NUMBER;

#endif // VALIDATION_ACTIVE


    // Poisoning the values
    for (int i = 0; i < stackObject->size; ++i) {
        stackObject->data[i] = (StackElem_t) POISON_VALUES::NUMBER;
    }

    // freeing allocated memory
    free(stackObject->data);

    //destroying attributes
    stackObject->name        = (char*)        POISON_VALUES::POINTER;
    stackObject->data        = (StackElem_t*) POISON_VALUES::POINTER;
    stackObject->self        = (Stack_t*)     POISON_VALUES::POINTER;
    stackObject->size        = (size_t)       POISON_VALUES::NUMBER;
    stackObject->capacity    = (size_t)       POISON_VALUES::NUMBER;

    // destroying methods
    stackObject->top  = (StackElem_t (*)(stack*))                          POISON_VALUES::POINTER;
    stackObject->pop  = (ERROR_CODE (*)(stack*))                           POISON_VALUES::POINTER;
    stackObject->push = (ERROR_CODE (*)(stack*, StackElem_t))              POISON_VALUES::POINTER;
    stackObject->dump = (void (*)(stack*, const char*, FILE*, Location_t)) POISON_VALUES::POINTER;
}


ERROR_CODE StackNew(Stack_t** stackObject_ptr, const char* name)
{
    assert(stackObject_ptr && name && "Stack object initialization failed");

    *stackObject_ptr = (Stack_t*) calloc(1, sizeof (Stack_t));

    return StackCtor(*stackObject_ptr, name);
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

    if (VALIDATION_DEPTH >= 1) {

    }

    if (VALIDATION_DEPTH >= 2) {
    }

    if (VALIDATION_DEPTH >= 3) {

    }

    return true;
}


ERROR_CODE SecureRealloc(StackElem_t** buffer, size_t nElements, size_t elemSize)
{
    assert(buffer && "Inapropriate pointer");

    void* dataTmp = realloc(*buffer, nElements * elemSize);

    if (dataTmp)
        *buffer = (StackElem_t*) dataTmp;
    else
        return ALLOCATION_ERROR;

    return NO_ERROR;
}


ERROR_CODE NumberValid(StackElem_t value)
{
    if (value == (StackElem_t) POISON_VALUES::NUMBER)
        return POISON_NUMBER;

    return NO_ERROR;
}


ERROR_CODE SizeValid(size_t size, size_t capacity)
{
    if (size > capacity)
        return CAPACITY_ERROR;

    return NO_ERROR;
}


ERROR_CODE PointerValid(void* pointer)
{
    if (pointer == nullptr)
        return POINTER_IS_NULL;
    else if (pointer == (void*) POISON_VALUES::POINTER)
        return POISON_POINTER;

    return NO_ERROR;
}


ERROR_CODE HashValid(void* data, size_t dataSize, Hash_t hash)
{
    assert(data && "Inapropriate pointer");

    if (CalculateHash(data, dataSize) != hash)
        return INVALID_HASH;

    return NO_ERROR;
}


ERROR_CODE CanaryValid(Stack_t* stackObject, Stack_t* canary)
{
    assert(canary && stackObject && "Inapropriate pointer");

    if (stackObject->self != canary)
        return CANARY_ACCESSED;

    return NO_ERROR;
}


ERROR_CODE IncreaseCapacity(Stack_t* stackObject)
{
    assert(stackObject  && "Invalid pointer to the stack object");

    if (SecureRealloc(&stackObject->data, stackObject->capacity * INCREMENT_COEFF, sizeof (StackElem_t)) == NO_ERROR)
        stackObject->capacity *= INCREMENT_COEFF;
    else {
        RETURN(ALLOCATION_ERROR);
    }

    for (size_t i = stackObject->size; i < stackObject->capacity; ++i) {
        stackObject->data[i] = (StackElem_t) POISON_VALUES::NUMBER;
    }

    RETURN(NO_ERROR);
}


ERROR_CODE DecreaseCapacity(Stack_t* stackObject)
{
    assert(stackObject  && "Invalid pointer to the stack object");

    if (SecureRealloc(&stackObject->data, (stackObject->capacity / DECREMENT_COEFF), sizeof (StackElem_t)) == NO_ERROR) {
        stackObject->capacity /= DECREMENT_COEFF;
    }
    else {
        RETURN(ALLOCATION_ERROR);
    }

    RETURN(NO_ERROR);
}
