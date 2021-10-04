/**
 * @file Stack.h
 */

#ifndef STACK_STACK_H
#define STACK_STACK_H

/// Standard libs
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

/// Self-written libs
#include "Location.h"
#include "Validate.h"
#include "Errors.h"
#include "Hash.h"


const Hash_t NEUTRAL_HASH = 77777;


#define VALIDATION_ACTIVE

#ifdef VALIDATION_ACTIVE
    #define VALIDATION_DEPTH HARD
#endif


#ifdef VALIDATION_ACTIVE
    #define ON_DEBUG(expr) expr
#else
    #define ON_DEBUG(expr)
#endif


//{--------------------------------Stack_t-init-macroses-------------------------------------------

#define Stack_t(name)                           \
                                                \
Stack_t name = {};                              \
if (StackCtor(&name, #name) != NO_ERROR)        \
    assert(0 && "Stack construction failed")    

#define new_Stack_t(name)                       \
                                                \
Stack_t* name = nullptr;                        \
if (StackNew(&name, #name) != NO_ERROR)         \
    assert(0 && "Stack construction failed")    


#define delete_Stack_t(name)                    \
                                                \
if (StackNew(&name, #name) != NO_ERROR)         \
    assert(0 && "Stack construction failed")    

//}------------------------------------------------------------------------------------------------


//{--------------------------------Validation-levels-----------------------------------------------

enum ValidationDepth {
    NO_VALIDATION = 0,      /// does no validation
    EASY          = 1,      /// checks only stack's fields
    MEDIUM        = 2,      /// checks canaries
    HARD          = 3       /// checks hashes
};
//}------------------------------------------------------------------------------------------------


//{--------------------------------Poison-values---------------------------------------------------

enum class POISON_VALUES {
    POINTER = 666,              /// Pointer poison value
    NUMBER  = 0xDEADBEE,        /// Hex number poison value
};
//}------------------------------------------------------------------------------------------------


//{--------------------------------Stack_t-"class"-------------------------------------------------

typedef uint64_t StackElem_t;


typedef struct stack {

// left canary
    ON_DEBUG(stack* canaryLeft = nullptr);

// attributes
    size_t size       = 0;
    size_t capacity   = 0;
    stack* self       = nullptr;
    const char* name  = nullptr;
    StackElem_t* data = nullptr;

// methods
    StackElem_t (*top)  (stack* self)                                                = nullptr;
    ERROR_CODE  (*pop)  (stack* self)                                                = nullptr;
    ERROR_CODE  (*push) (stack* self, StackElem_t value)                             = nullptr;
    void        (*dump) (stack* self, const char* localName, FILE* dest, Location_t) = nullptr;

// Hash
    ON_DEBUG(Hash_t hash = NEUTRAL_HASH);

// right canary
    ON_DEBUG(stack* canaryRight = nullptr);

} Stack_t;
//}------------------------------------------------------------------------------------------------


//{--------------------------------Stack-methods---------------------------------------------------

/**
 * Removes the last element put into stack
 * @param[in,out] stackObject pointer to the stack object
 * @return operation success status (ERROR_CODE)
 */
static ERROR_CODE StackPop(Stack_t* stackObject);

/**
 * Puts an element into stack
 * @param[in,out] stackObject pointer to the stack object
 * @param[in] value a value to put
 * @return operation success status (ERROR_CODE)
 */
static ERROR_CODE StackPush(Stack_t* stackObject, StackElem_t value);

/**
 * Dumps stack info into a file
 * @param[in] stackObject pointer to the stack object
 * @param[in] localName local stack name
 * @param[in] destFile a file to put info in
 * @param[in] location location of the variable
 */
static void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile, Location_t location);

/**
 * Returns first from the top stack element
 * @param[in] stackObject pointer to the stack object
 * @return top element
 */
static StackElem_t StackTop(Stack_t* stackObject);
//}------------------------------------------------------------------------------------------------


//{------------------------Stack-constructors-and-destructors--------------------------------------

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


//{------------------------Validation-related-functions--------------------------------------------
/**
 * Data protection related functions
 */


/**
 * Checks stack for errors
 * @param[in] stackObject
 * @return stack validation status (bool)
 */
bool StackValid(Stack_t* stackObject);

/**
 * Checks number for errors
 * @param[in] value
 * @return number validation status (ERROR_CODE)
 */
ERROR_CODE NumberValid(StackElem_t value);

/**
 * Checks size value for errors
 * @param[in] size stack size
 * @param[in] capacity stack capacity
 * @return size validation status (ERROR_CODE)
 */
ERROR_CODE SizeValid(size_t size, size_t capacity);

/**
 * Checks pointer for errors
 * @param[in] pointer some pointer
 * @return pointer validation status (ERROR_CODE)
 */
ERROR_CODE PointerValid(void* pointer);

/**
 * Checks hash for errors
 * @param[in] data
 * @param[in] dataSize
 * @param[in] hash
 * @return hash validation status (ERROR_CODE)
 */
ERROR_CODE HashValid(Stack_t* stackObject);

/**
 * Checks canary for errors
 * @param[in] stackObject pointer to the stack object
 * @param[in] canary pointer to the canary
 * @return canary validation status (ERROR_CODE)
 */
ERROR_CODE CanaryValid(Stack_t* stackObject, Stack_t* canary);
//}------------------------------------------------------------------------------------------------

#endif // STACK_STACK_H
