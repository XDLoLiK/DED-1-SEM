/**
 * @file Stack.cpp
 */

#include "Stack.h"

bool Stack_push(Stack_t* stackObject, StackElem_t value)
{
    VALIDATE(stackObject, Stack_is_valid, Stack_dump)

    stackObject->data = (StackElem_t*) realloc(stackObject->data, stackObject->size + 1);
    stackObject->size += 1;
    stackObject->data[stackObject->size - 1] = value;

    VALIDATE(stackObject, Stack_is_valid, Stack_dump)

    return true;
}

bool Stack_pop(Stack_t* stackObject)
{
    VALIDATE(stackObject, Stack_is_valid, Stack_dump)

    stackObject->data[stackObject->size - 1] = (StackElem_t) POISON_VALUES::number;
    stackObject->data = (StackElem_t*) realloc(stackObject->data, stackObject->size - 1);
    stackObject->size -= 1;

    VALIDATE(stackObject, Stack_is_valid, Stack_dump)

    return true;
}

bool Stack_dump(Stack_t* stackObject, const char* localName)
{
    return true;
}

bool Stack_ctor(Stack_t* stackObject, const char* name)
{
    assert(stackObject && name && "Stack object initialization failed");

    stackObject->self = stackObject;
    stackObject->name = name;
    stackObject->size = 0;

    assert(&Stack_push && &Stack_pop && &Stack_dump);

    stackObject->push = &Stack_push;
    stackObject->pop = &Stack_pop;
    stackObject->dump = &Stack_dump;

    return true;
}

bool Stack_dtor(Stack_t* stackObject)
{
    VALIDATE(stackObject, Stack_is_valid, Stack_dump)

    // Poisoning the values
    for (int elemN = 0; elemN < stackObject->size; ++elemN) {
        stackObject->data[elemN] = (StackElem_t) POISON_VALUES::number;
    }

    // destroying methods
    stackObject->pop = (bool (*)(stack*)) POISON_VALUES::pointer;
    stackObject->push = (bool (*)(stack*, StackElem_t)) POISON_VALUES::pointer;
    stackObject->dump = (bool (*)(stack*, const char*)) POISON_VALUES::pointer;

    //destroying attributes
    stackObject->name = (char*) POISON_VALUES::pointer;
    stackObject->data = (StackElem_t*) POISON_VALUES::pointer;
    stackObject->self = (Stack_t*) POISON_VALUES::pointer;
    stackObject->size = (size_t) POISON_VALUES::number;

    return true;
}

bool Stack_new(Stack_t** stackObject_ptr, const char* name)
{
    assert(stackObject_ptr && name && "Stack object initialization failed");

    *stackObject_ptr = (Stack_t*) calloc(1, sizeof (Stack_t));
    Stack_ctor(*stackObject_ptr, name);

    return true;
}

bool Stack_is_valid(Stack_t* stackObject)
{
    if (VALIDATION_DEPTH == 1) {

    } else if (VALIDATION_DEPTH == 2) {

    } else if (VALIDATION_DEPTH == 3) {

    }

    return true;
}

bool Stack_delete(Stack_t** stackObject_ptr)
{
    Stack_dtor(*stackObject_ptr);
    free(*stackObject_ptr);

    return true;
}
