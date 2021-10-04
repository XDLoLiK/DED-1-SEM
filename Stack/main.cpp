/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t (array); 

    StackDtor(array.self);

    StackDump(array.self, "", stdout, __LOCATION__);

    StackCtor(array.self, "array");

    return 0;
}
