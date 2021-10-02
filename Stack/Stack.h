/**
 * @file Stack.h
 */

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

#include "Location.h"
#include "Validate.h"
#include "Hash.h"

#define VALIDATION_ACTIVE

#ifdef VALIDATION_ACTIVE
    #define VALIDATION_DEPTH HARD
#endif

//{------------------------------------------------------------------------------------------------
/**
 * Stack_t init macroses
 */

#define Stack_t(name)                        \
Stack_t name = {};                           \
if (StackCtor(&name, #name) != NO_ERROR)     \
    assert(0 && "Stack construction failed")     //!!!!!!!!!!~~~~~~~

#define new_Stack_t(name)        \
Stack_t* name = nullptr;         \
if (!StackNew(&name, #name))     \
    assert(0)


#define delete_Stack_t(name)     \
if (!StackNew(&name, #name))     \
    assert(0)

//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Validation depth levels
 */

enum ValidationDepth {
    NO_VALIDATION = 0, /// does no validation
    EASY          = 1, /// checks only stack's fields
    MEDIUM        = 2, /// checks canaries
    HARD          = 3  /// checks hashes
};
//}------------------------------------------------------------------------------------------------

#define ERROR_LOG(ErrorName) {                                                          \
    Location_t location = __LOCATION__;                                                 \
                                                                                        \
    if ((ErrorName) != NO_ERROR) {                                                      \
        printf("=================================================================\n");  \
        printf(">>> ERROR OCCURRED!\n");                                                \
        printf(">>> REASON:   %s\n", #ErrorName);                                       \
        printf(">>> FILE:     %s\n", location.file);                                    \
        printf(">>> FUNCTION: %s\n", location.function);                                \
        printf(">>> LINE:     %d\n", location.line);                                    \
        printf("=================================================================\n");  \
    }                                                                                   \
}                                                                                       \
                                                                                        \
do {                                                                                    \
                                                                                        \
} while(0)

#define RETURN(ErrorName)                   \
    ERROR_LOG(ErrorName);                   \
    return ErrorName

enum ERROR_CODE {
    NO_ERROR                    = 0,
    INVALID_HASH                = 1,
    POISON_NUMBER               = 2,
    CAPACITY_ERROR              = 3,
    POINTER_IS_NULL             = 4,
    CANARY_ACCESSED             = 5,
    ALLOCATION_ERROR            = 6,
    POISON_POINTER              = 7,
    INITIALIZATION_ERROR        = 8,
    CAPACITY_DECREMENT_ERROR    = 9,
    CAPACITY_INCREMENT_ERROR    = 10,
    EMPTY_STACK_POP_ATTEMPT     = 11,
    EMPTY_STACK_TOP_ATTEMPT     = 12
};

//{------------------------------------------------------------------------------------------------
/**
 * Poison values
 * (to poison the freed data)
 */

enum class POISON_VALUES {
    POINTER = 666,       /// Pointer poison value
    NUMBER  = 0xDEADBEE, /// Hex poison number value
};
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Stack_t "class"
 */

typedef uint64_t StackElem_t;

typedef struct stack {

#ifdef VALIDATION_ACTIVE
// left canary
    stack* canaryLeft = nullptr;
#endif

// attributes
    size_t size       = 0;
    size_t capacity   = 0;
    const char* name  = nullptr;
    stack* self       = nullptr;
    StackElem_t* data = nullptr;

// methods

    StackElem_t (*top)  (stack* self)                                                = nullptr;
    ERROR_CODE  (*pop)  (stack* self)                                                = nullptr;
    ERROR_CODE  (*push) (stack* self, StackElem_t value)                             = nullptr;
    void        (*dump) (stack* self, const char* localName, FILE* dest, Location_t) = nullptr;

#ifdef VALIDATION_ACTIVE
// Hash
    Hash_t hash = 0;

// right canary
    stack* canaryRight = nullptr;
#endif

} Stack_t;
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Stack methods
 */

/**
 * Removes the last element put into stack
 * @param[in,out] stackObject pointer to the stack object
 * @return operation success status (ERROR_CODE)
 */
ERROR_CODE StackPop(Stack_t* stackObject);

/**
 * Puts an element into stack
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] value a value to put
 * @return operation success status (ERROR_CODE)
 */
ERROR_CODE StackPush(Stack_t* stackObject, StackElem_t value);

/**
 * Dumps stack info into a file
 * @param[in] stackObject pointer to the stack object
 * @param[in] localName local stack name
 * @param[in] destFile a file to put info in
 * @param[in] location location of the variable
 */
void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile, Location_t location);

/**
 * Returns first from the top stack element
 * @param[in] stackObject pointer to the stack object
 * @return top element
 */
StackElem_t StackTop(Stack_t* stackObject);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Stack constructors and destructors
 */

/**
 * Initializes stack data on the static memory
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] name initialization stack variable name
 * @return operation success status (ERROR_CODE)
 */
ERROR_CODE StackCtor(Stack_t* stackObject, const char* name);

/**
 * Initializes stack data on the dynamic memory
 * @param[in,out] stackObject pointer to the stack object
 */
void StackDtor(Stack_t* stackObject);

/**
 * Frees stack fields and memory
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] name
 * @return operation success status (ERROR_CODE)
 */
ERROR_CODE StackNew(Stack_t** stackObject, const char* name);

/**
 * Frees stack fields and memory
 * @param[in,out] stackObject_ptr pointer to the stack object
 */
void StackDelete(Stack_t** stackObject_ptr);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Data protection related functions
 */

/**
 * Checks realloc result before assignment
 * @param[in,out] buffer pointer to the buffer
 * @param[in] nElements number of elements in the buffer
 * @param[in] elemSize size of one element
 * @return realloc status (ERROR_CODE)
 */
ERROR_CODE SecureRealloc(StackElem_t** buffer, size_t nElements, size_t elemSize);

/**
 * Checks stack for errors
 * @param[in] stackObject
 * @return stack validation status (bool)
 */
bool StackValid(Stack_t* stackObject);

/**
 * Checks number for errors
 * @param[in] value
 * @return
 */
ERROR_CODE NumberValid(StackElem_t value);

/**
 * Checks size value for errors
 * @param size
 * @param capacity
 * @return
 */
ERROR_CODE SizeValid(size_t size, size_t capacity);

/**
 * Checks pointer for errors
 * @param pointer
 * @return
 */
ERROR_CODE PointerValid(void* pointer);

/**
 * Checks hash for errors
 * @param data
 * @param dataSize
 * @param hash
 * @return
 */
ERROR_CODE HashValid(void* data, size_t dataSize, Hash_t hash);

/**
 * Checks canary for errors
 * @param stackObject
 * @param canary
 * @return
 */
ERROR_CODE CanaryValid(Stack_t* stackObject, Stack_t* canary);
//}------------------------------------------------------------------------------------------------

#endif // STACK_STACK_H
