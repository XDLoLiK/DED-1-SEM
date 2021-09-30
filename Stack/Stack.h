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

#define $meow printf("Meow");

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

enum class POISON_VALUES {
    pointer = 666,
    number  = 0xDEDBEEF,
    symbol  = 1
};

enum class ERROR_CODES {
    NO_ERROR       = 0,
    POISON_VALUE   = 1,
    CAPACITY_FAULT = 2,
    LACK_OF_MEMORY = 3
};

//#define STK_SUCCESS(status) status == NO_ERROR ????????????????????????????????????????????????

//{------------------------------------------------------------------------------------------------
/**
 * Stack_t "class"
 */

typedef double   StackElem_t;

typedef struct stack {

// attributes
    size_t size       = 0;
    size_t capacity   = 0;
    const char* name  = nullptr;
    stack* self       = nullptr;
    StackElem_t top   = (StackElem_t) POISON_VALUES::number;
    StackElem_t* data = nullptr;

// methods
    bool (*pop)  (stack* self)                                    = nullptr;
    void (*dump) (stack* self, const char* localName, FILE* dest) = nullptr;
    bool (*push) (stack* self, StackElem_t value)                 = nullptr;

// Hash
    Hash_t hash = 0;

} Stack_t;
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Stack methods
 */

bool StackPop(Stack_t* stackObject);
bool StackPush(Stack_t* stackObject, StackElem_t value);
void StackDump(Stack_t* stackObject, const char* localName, FILE* destFile);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Stack constructors and destructors
 */

bool StackCtor(Stack_t* stackObject, const char* name);
void StackDtor(Stack_t* stackObject);
bool StackNew(Stack_t** stackObject, const char* name);
void StackDelete(Stack_t** stackObject_ptr);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Data protection related functions
 */

bool ReallocSuccess(StackElem_t** buffer, size_t nElements, size_t elemSize);
bool StackValid(Stack_t* stackObject);
//}------------------------------------------------------------------------------------------------

#endif // STACK_STACK_H
