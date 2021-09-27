/**
 * @file Stack.h
 */

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Location.h"
#include "Validate.h"

#define VALIDATION_DEPTH 1

//{------------------------------------------------------------------------------------------------
/**
 * Stack_t init macroses
 */

#define Stack_t(name)             \
Stack_t name = {};                \
if (!Stack_ctor(&name, #name)) {  \
    assert(0);                    \
}

#define new_Stack_t(name)        \
Stack_t* name = nullptr;         \
if (!Stack_new(name, #name)) {   \
    assert(0);                   \
}

#define delete_Stack_t(name)     \
if (!Stack_new(name, #name)) {   \
    assert(0);                   \
}
//}------------------------------------------------------------------------------------------------

enum class POISON_VALUES{
    pointer = 666,
    number = -32768,
    symbol = '\0'
};

enum class ERROR_CODES{
    NO_ERROR = 0,
    POISON_VALUE = 1
};

//{------------------------------------------------------------------------------------------------
/**
 * Stack_t "class"
 */

typedef double StackElem_t;

typedef struct stack{
    // attributes
    size_t size = 0;
    size_t capacity = 0;
    stack* self = nullptr;
    const char* name = nullptr;
    StackElem_t* data = nullptr;
    // methods
    bool (*pop) (stack* self) = nullptr;
    bool (*dump) (stack* self, const char* localName) = nullptr;
    bool (*push) (stack* self, StackElem_t value) = nullptr;
} Stack_t;
//}------------------------------------------------------------------------------------------------

bool Stack_push(Stack_t* stackObject, StackElem_t value);
bool Stack_pop(Stack_t* stackObject);
bool Stack_dump(Stack_t* stackObject, const char* localName);

bool Stack_ctor(Stack_t* stackObject, const char* name);
bool Stack_dtor(Stack_t* stackObject);
bool Stack_new(Stack_t** stackObject, const char* name);
bool Stack_delete(Stack_t** stackObject_ptr);

bool Stack_is_valid(Stack_t* stackObject);

#endif // STACK_STACK_H
