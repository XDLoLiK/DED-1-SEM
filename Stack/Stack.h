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

#define IS_OK(type, value) strcmp(type##Valid(value), "ok") == 0

//{------------------------------------------------------------------------------------------------
/**
 * Stack_t init macroses
 */

#define Stack_t(name)            \
Stack_t name = {};               \
if (!StackCtor(&name, #name))    \
    assert(0)

#define new_Stack_t(name)        \
Stack_t* name = nullptr;         \
if (!StackNew(name, #name))      \
    assert(0)


#define delete_Stack_t(name)     \
if (!StackNew(name, #name))      \
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

#define ERROR_LOG(errorName) assert(! #errorName)

enum class ERROR_CODE {
    NO_ERROR                = 0,
    INVALID_HASH            = 1,
    POISON_VALUE            = 2,
    CAPACITY_ERROR          = 3,
    INVALID_POINTER         = 4,
    CANARY_ACCESSED         = 5,
    ALLOCATION_ERROR        = 6,
    INITIALIZATION_ERROR    = 7,
    };

//{------------------------------------------------------------------------------------------------
/**
 * Poison values
 * (to poison the freed data)
 */


enum class POISON_VALUES {
    pointer = 666,       /// Pointer poison value
    number  = 0xDEADBEE, /// Hex poison number value
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
    StackElem_t top   = (StackElem_t) POISON_VALUES::number;
    StackElem_t* data = nullptr;

// methods
    bool (*pop)  (stack* self)                                                = nullptr;
    void (*dump) (stack* self, const char* localName, FILE* dest, Location_t) = nullptr;
    bool (*push) (stack* self, StackElem_t value)                             = nullptr;

#ifdef VALIDATION_ACTIVE
// Hash
    Hash_t* stackHash = nullptr;
    Hash_t* dataHash = nullptr;

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
 * @return operation success status (bool)
 */
bool StackPop(Stack_t* stackObject);

/**
 * Puts an element into stack
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] value a value to put
 * @return operation success status (bool)
 */
bool StackPush(Stack_t* stackObject, StackElem_t value);

/**
 * Dumps stack info into a file
 * @param[in] stackObject pointer to the stack object
 * @param[in] localName local stack name
 * @param[in] destFile a file to put info in
 * @param[in] location location of the variable
 */
void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile, Location_t location);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Stack constructors and destructors
 */

/**
 * Initializes stack data on the static memory
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] name initialization stack variable name
 * @return operation success status (bool)
 */
bool StackCtor(Stack_t* stackObject, const char* name);

/**
 * Initializes stack data on the dynamic memory
 * @param[in,out] stackObject pointer to the stack object
 */
void StackDtor(Stack_t* stackObject);

/**
 * Frees stack fields and memory
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] name
 * @return operation success status (bool)
 */
bool StackNew(Stack_t** stackObject, const char* name);

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

bool SecureRealloc(StackElem_t** buffer, size_t nElements, size_t elemSize);

bool StackValid(Stack_t* stackObject);
const char* NumberValid(StackElem_t value);
const char* SizeValid(size_t size, size_t capacity);
const char* PointerValid(void* pointer);
const char* HashValid(void* data, size_t dataSize, Hash_t hash);
const char* CanaryValid(Stack_t* stackObject, Stack_t* canary);
//}------------------------------------------------------------------------------------------------

#endif // STACK_STACK_H
