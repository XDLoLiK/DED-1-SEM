/**
 * @file Stack.cpp
 */

#include "Stack.h"

/// Deacrese and increase capacity coefficients
const size_t INCREMENT_COEFF = 2;
const size_t DECREMENT_COEFF = 2;

//{--------------------------------------------------------User-unfriendly-functions-------------------------------------------------------
                                                                                                                                         //
/**                                                                                                                                      //
 * The user shall not have access to these                                                                                               //
 */                                                                                                                                      //
                                                                                                                                         //
/**                                                                                                                                      //
 * Increases stack object's capacity if possible                                                                                         //
 * @param[in,out] stackObject pointer to the stack object                                                                                //
 * @return error code (or no error)                                                                                                      //
 */                                                                                                                                      //
ERROR_CODE IncreaseCapacity(Stack_t* stackObject);                                                                                       //
                                                                                                                                         //
/**                                                                                                                                      //
 * Decreases stack object's capacity if possible                                                                                         //
 * @param[in,out] stackObject pointer to the stack object                                                                                //
 * @return error code (or no error)                                                                                                      //
 */                                                                                                                                      //
ERROR_CODE DecreaseCapacity(Stack_t* stackObject);                                                                                       //       
                                                                                                                                         //
/**                                                                                                                                      //
 * Checks realloc result before assignment                                                                                               //
 * @param[in,out] buffer pointer to the buffer                                                                                           //
 * @param[in] nElements number of elements in the buffer                                                                                 //
 * @param[in] elemSize size of one element                                                                                               //
 * @return realloc status (ERROR_CODE)                                                                                                   //
 */                                                                                                                                      //
ERROR_CODE SecureRealloc(StackElem_t** buffer, size_t nElements, size_t elemSize);                                                       //         
                                                                                                                                         //
/**                                                                                                                                      //
 * Computes hash for current stack object state                                                                                          //
 * @param[in,out] stackObject pointer to the stack object                                                                                //
 * @return new hash values                                                                                                               //
 */                                                                                                                                      //
Hash_t GetHash(Stack_t* stackObject);                                                                                                    //
//}----------------------------------------------------------------------------------------------------------------------------------------



//{--------------------------------------------------------Stack-methods-------------------------------------------------------------------

ERROR_CODE StackPush(Stack_t* stackObject, StackElem_t value) 
{
#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE

    if (IncreaseCapacity(stackObject->self) != NO_ERROR) 
        RETURN(ALLOCATION_ERROR);

    stackObject->data[stackObject->size++] = value;

#if defined(VALIDATION_ACTIVE)

    stackObject->hash = GetHash(stackObject->self);

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE

    RETURN(NO_ERROR);
} 


ERROR_CODE StackPop(Stack_t* stackObject)
{
#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE

    if (stackObject->size <= 0)
        RETURN(EMPTY_STACK_POP_ATTEMPT);

    if (DecreaseCapacity(stackObject->self) != NO_ERROR)
        RETURN(ALLOCATION_ERROR);

    stackObject->data[--stackObject->size] = (StackElem_t) POISON_VALUES::NUMBER;

#if defined(VALIDATION_ACTIVE)

    stackObject->hash = GetHash(stackObject->self);

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE

    RETURN(NO_ERROR);
}


StackElem_t StackTop(Stack_t* stackObject)
{
#if defined(VALIDATION_ACTIVE)

    VALIDATE(stackObject, StackValid, StackDump);

#endif // VALIDATION_ACTIVE

    if (stackObject->size <= 0) 
        RETURN(EMPTY_STACK_TOP_ATTEMPT);

    return stackObject->data[stackObject->size - 1];
}


#if defined(VALIDATION_ACTIVE) 

void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile, Location_t location)
{
    assert(stackObject && localName && destFile && "Inapropriate pointer");

    const char* stackStatus = (StackValid(stackObject->self)) ? "ok" : "ERROR!";
    
    fprintf(destFile, "\nstack<Stack_t> \"%s\" [%p] (%s) %s: %s(%d) aka \"%s\":\n\n", 
            stackObject->name, stackObject->self, stackStatus, location.file, location.function, location.line, localName);

    const char* sizeStatus = (SizeValid(stackObject->size, stackObject->capacity) == NO_ERROR) ? "ok" : "ERROR!";
    const char* capacityStatus = sizeStatus;

    fprintf(destFile,
            "\tsize_t size        = %-10zd (%s)\n"
            "\tsize_t capacity    = %-10zd (%s)\n",
            stackObject->size, sizeStatus, stackObject->capacity, capacityStatus);

    const char* leftCanaryStatus  = (CanaryValid(stackObject->self, stackObject->canaryLeft)  == NO_ERROR) ? "ok" : "ERROR!";
    const char* rightCanaryStatus = (CanaryValid(stackObject->self, stackObject->canaryRight) == NO_ERROR) ? "ok" : "ERROR!";

    fprintf(destFile,
            "\tstack* canaryLeft  = %-10llu (%s)\n"
            "\tstack* canaryRight = %-10llu (%s)\n",
            stackObject->canaryLeft, leftCanaryStatus, stackObject->canaryRight, rightCanaryStatus);

    const char* hashStatus = (HashValid(stackObject->self) == NO_ERROR) ? "ok" : "ERROR!";

    fprintf(destFile,
            "\tHash_t hash        = %-10llu (%s)\n"
            "\tCorrect hash       = %-10llu\n\n",
            stackObject->hash, hashStatus, GetHash(stackObject->self));   

    bool dataIsOk = true;

    for (int i = 0; i < stackObject->size; ++i) 
        dataIsOk = NumberValid(stackObject->data[i]);

    const char* dataStatus = (dataIsOk) ? "ok" : "ERROR!";

    fprintf(destFile,
            "\tStackElem_t* data [%p] (%s) {\n\n",
            stackObject->data, dataStatus);   

    const char* valueStatus = nullptr;

    for (int i = 0; i < stackObject->size; ++i) {
        valueStatus = (NumberValid(stackObject->data[i]) == NO_ERROR) ? "ok" : "ERROR!";
        fprintf(destFile,
                "\t\t*[%d] = %llu (%s);\n", i, stackObject->data[i], valueStatus);
    }

    for (int i = stackObject->size; i < stackObject->capacity; ++i) {
        valueStatus = (NumberValid(stackObject->data[i]) == NO_ERROR) ? "ok" : "ERROR!";
        fprintf(destFile,
                "\t\t[%d] = %llu;\n", i, stackObject->data[i], valueStatus);
    }

    fprintf(destFile, "\t}\n\n");
}

#endif // VALIDATION_ACTIVE 
//}----------------------------------------------------------------------------------------------------------------------------------------


//}--------------------------------------------------------Construction-and-destruction-fuctions-------------------------------------------
                                                                                                                                         //
ERROR_CODE StackCtor(Stack_t* stackObject, const char* name)                                                                             //
{                                                                                                                                        //
    if (stackObject == nullptr || name == nullptr)                                                                                       //
        RETURN(INITIALIZATION_ERROR);                                                                                                    //
                                                                                                                                         //
    // defining attributes                                                                                                               //
    stackObject->size = 0;                                                                                                               //
    stackObject->name = name;                                                                                                            //
    stackObject->self = stackObject;                                                                                                     //
                                                                                                                                         //
    if (SecureRealloc(&stackObject->data, 1, sizeof (StackElem_t)) == NO_ERROR)                                                          //
        stackObject->capacity = 1;                                                                                                       //
    else                                                                                                                                 //
        RETURN(ALLOCATION_ERROR);                                                                                                        //
                                                                                                                                         //
    stackObject->data[0] = 0;                                                                                                            //
                                                                                                                                         //
    // setting up the canaries                                                                                                           //
                                                                                                                                         //
    assert(&StackPop && &StackPush && &StackDump && &StackTop && "Invalid function pointer");                                            //
                                                                                                                                         //
    // defining methods                                                                                                                  //
    stackObject->pop  = &StackPop;                                                                                                       //
    stackObject->top  = &StackTop;                                                                                                       //
    stackObject->push = &StackPush;                                                                                                      //
    stackObject->dump = &StackDump;                                                                                                      //
                                                                                                                                         //                                                                                                                                         
#if defined(VALIDATION_ACTIVE)                                                                                                           //
                                                                                                                                         //                                                                                                                                                                                                                               
    // setting canaries                                                                                                                  //
    stackObject->canaryLeft  = stackObject->self;                                                                                        //
    stackObject->canaryRight = stackObject->self;                                                                                        //
                                                                                                                                         //
    // calculatig hash                                                                                                                   //
    stackObject->hash = GetHash(stackObject->self);                                                                                      //
                                                                                                                                         //
    VALIDATE(stackObject, StackValid, StackDump);                                                                                        //
                                                                                                                                         //
#endif // VALIDATION_ACTIVE                                                                                                              //                                                                                                                                                                                                                                                                            
    RETURN(NO_ERROR);                                                                                                                    //
}                                                                                                                                        //
                                                                                                                                         //                       
                                                                                                                                         //
Hash_t GetHash(Stack_t* stackObject)                                                                                                     //
{                                                                                                                                        //
    Hash_t oldHash    = stackObject->hash;                                                                                               //
    stackObject->hash = NEUTRAL_HASH;                                                                                                    //
                                                                                                                                         //
    Hash_t structHash = CalculateHash(stackObject->self, sizeof stackObject);                                                            //
    Hash_t dataHash   = CalculateHash(stackObject->data, sizeof (StackElem_t) * stackObject->capacity);                                  //
                                                                                                                                         //
    stackObject->hash = oldHash;                                                                                                         //
                                                                                                                                         //
    return structHash ^ dataHash;                                                                                                        //
}                                                                                                                                        //
                                                                                                                                         //
                                                                                                                                         //
void StackDtor(Stack_t* stackObject)                                                                                                     //
{                                                                                                                                        //
#if defined(VALIDATION_ACTIVE)                                                                                                           //
                                                                                                                                         //
    VALIDATE(stackObject, StackValid, StackDump);                                                                                        //
                                                                                                                                         //
    stackObject->canaryLeft  = (Stack_t*)  POISON_VALUES::POINTER;                                                                       //
    stackObject->canaryRight = (Stack_t*)  POISON_VALUES::POINTER;                                                                       //
    stackObject->hash        = (Hash_t)    POISON_VALUES::NUMBER;                                                                        //
                                                                                                                                         //
#endif // VALIDATION_ACTIVE                                                                                                              //
                                                                                                                                         //
    // Poisoning the values                                                                                                              //
    for (int i = 0; i < stackObject->size; ++i) {                                                                                        //
        stackObject->data[i] = (StackElem_t) POISON_VALUES::NUMBER;                                                                      //
    }                                                                                                                                    //
                                                                                                                                         //
    // freeing allocated memory                                                                                                          //
    free(stackObject->data);                                                                                                             //
                                                                                                                                         //
    //destroying attributes                                                                                                              //
    stackObject->name        = (char*)        POISON_VALUES::POINTER;                                                                    //
    stackObject->data        = (StackElem_t*) POISON_VALUES::POINTER;                                                                    //
    stackObject->self        = (Stack_t*)     POISON_VALUES::POINTER;                                                                    //
    stackObject->size        = (size_t)       POISON_VALUES::NUMBER;                                                                     //
    stackObject->capacity    = (size_t)       POISON_VALUES::NUMBER;                                                                     //
                                                                                                                                         //
    // destroying methods                                                                                                                //
    stackObject->top  = (StackElem_t (*)(stack*))                          POISON_VALUES::POINTER;                                       //
    stackObject->pop  = (ERROR_CODE (*)(stack*))                           POISON_VALUES::POINTER;                                       //
    stackObject->push = (ERROR_CODE (*)(stack*, StackElem_t))              POISON_VALUES::POINTER;                                       //
    stackObject->dump = (void (*)(stack*, const char*, FILE*, Location_t)) POISON_VALUES::POINTER;                                       //
}                                                                                                                                        //
                                                                                                                                         //
                                                                                                                                         //
ERROR_CODE StackNew(Stack_t** stackObject_ptr, const char* name)                                                                         //
{                                                                                                                                        //
    assert(stackObject_ptr && name && "Stack object initialization failed");                                                             //
                                                                                                                                         //
    *stackObject_ptr = (Stack_t*) calloc(1, sizeof (Stack_t));                                                                           //
                                                                                                                                         //
    return StackCtor(*stackObject_ptr, name);                                                                                            //
}                                                                                                                                        //
                                                                                                                                         //
                                                                                                                                         //
void StackDelete(Stack_t** stackObject_ptr)                                                                                              //
{                                                                                                                                        //
    assert(stackObject_ptr && "Inapropriate pointer");                                                                                   //
                                                                                                                                         //
    StackDtor(*stackObject_ptr);                                                                                                         //
    free(*stackObject_ptr);                                                                                                              //
}                                                                                                                                        //
//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Validation-functions------------------------------------------------------------

bool StackValid(Stack_t* stackObject)
{
    assert(stackObject && "Inapropriate pointer");

    bool validator = true;

    if (VALIDATION_DEPTH >= 1) {

        validator = (PointerValid((void*) stackObject->top)  == NO_ERROR &&
                     PointerValid((void*) stackObject->pop)  == NO_ERROR &&
                     PointerValid((void*) stackObject->push) == NO_ERROR &&
                     PointerValid((void*) stackObject->dump) == NO_ERROR &&
                     PointerValid((void*) stackObject->self) == NO_ERROR &&
                     PointerValid((void*) stackObject->name) == NO_ERROR &&
                     PointerValid((void*) stackObject->data) == NO_ERROR &&
                     SizeValid(stackObject->size, stackObject->capacity) == NO_ERROR);
    }

    if (VALIDATION_DEPTH >= 2) {
        validator = (CanaryValid(stackObject->self, stackObject->canaryLeft)  == NO_ERROR &&
                     CanaryValid(stackObject->self, stackObject->canaryRight) == NO_ERROR);
    }

    if (VALIDATION_DEPTH >= 3) {
        validator = HashValid(stackObject) == NO_ERROR;
    }

    return validator;
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


ERROR_CODE HashValid(Stack_t* stackObject)
{
    assert(stackObject && "Inapropriate pointer");

    Hash_t oldHash     = stackObject->hash;
    stackObject->hash  = NEUTRAL_HASH;
    Hash_t currentHash = GetHash(stackObject->self);

    if (oldHash != currentHash)
        return INVALID_HASH;
    else
        stackObject->hash = oldHash;

    return NO_ERROR;
}


ERROR_CODE CanaryValid(Stack_t* stackObject, Stack_t* canary)
{
    assert(canary && stackObject && "Inapropriate pointer");

    if (stackObject->self != canary)
        return CANARY_ACCESSED;

    return NO_ERROR;
}
//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Memory-realloc-functions--------------------------------------------------------
                                                                                                                                         //
ERROR_CODE SecureRealloc(StackElem_t** buffer, size_t nElements, size_t elemSize)                                                        //
{                                                                                                                                        //           
    assert(buffer && "Inapropriate pointer");                                                                                            //
                                                                                                                                         //
    StackElem_t* dataTmp = (StackElem_t*) realloc(*buffer, nElements * elemSize);                                                        //
                                                                                                                                         //
    if (dataTmp)                                                                                                                         //
        *buffer = dataTmp;                                                                                                               //
    else                                                                                                                                 //
        return ALLOCATION_ERROR;                                                                                                         //
                                                                                                                                         //
    return NO_ERROR;                                                                                                                     //
}                                                                                                                                        //
                                                                                                                                         //
                                                                                                                                         //
ERROR_CODE IncreaseCapacity(Stack_t* stackObject)                                                                                        //
{                                                                                                                                        //
    assert(stackObject  && "Invalid pointer to the stack object");                                                                       //
                                                                                                                                         //
    if (stackObject->size == stackObject->capacity) {                                                                                    //
                                                                                                                                         //
        if (SecureRealloc(&stackObject->data, stackObject->capacity * INCREMENT_COEFF, sizeof (StackElem_t)) == NO_ERROR)                //
            stackObject->capacity *= INCREMENT_COEFF;                                                                                    //
        else                                                                                                                             //
            return ALLOCATION_ERROR;                                                                                                     //                                                                                                                       
    }                                                                                                                                    //
                                                                                                                                         //
    for (size_t i = stackObject->size; i < stackObject->capacity; ++i) {                                                                 //
        stackObject->data[i] = (StackElem_t) POISON_VALUES::NUMBER;                                                                      //
    }                                                                                                                                    //
                                                                                                                                         //
    return NO_ERROR;                                                                                                                     //
}                                                                                                                                        //
                                                                                                                                         //
                                                                                                                                         //
ERROR_CODE DecreaseCapacity(Stack_t* stackObject)                                                                                        //
{                                                                                                                                        //
    assert(stackObject  && "Invalid pointer to the stack object");                                                                       //
                                                                                                                                         //
    /// a point when it's time to decrease the capacity                                                                                  //
    size_t decrementPoint = stackObject->capacity / 4;                                                                                   //
                                                                                                                                         //
    if (stackObject->size <= decrementPoint) {                                                                                           //
                                                                                                                                         //
        if (SecureRealloc(&stackObject->data, stackObject->capacity / DECREMENT_COEFF, sizeof (StackElem_t)) == NO_ERROR)                //
            stackObject->capacity /= DECREMENT_COEFF;                                                                                    //
        else                                                                                                                             //
            return ALLOCATION_ERROR;                                                                                                     //                                                                                                                                
    }                                                                                                                                    //
                                                                                                                                         //
    return NO_ERROR;                                                                                                                     //
}                                                                                                                                        //
//}----------------------------------------------------------------------------------------------------------------------------------------
