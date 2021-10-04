/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t (array); 

    array.push(array.self, 1);
    array.top(array.self);
    array.pop(array.self);
    array.top(array.self);
    array.pop(array.self);

    for (int i = 0; i < 100; ++i) {
        array.push(array.self, i);
    }

    array.dump(array.self, "", stdout, __LOCATION__);

    for (int i = 0; i < 100; ++i) {
        array.pop(array.self);
    }

    // array.hash = 1;
    // array.push(array.self, 0);

    // array.data[0] = 555;
    // array.push(array.self, 0);

    // array.data = nullptr;
    // array.push(array.self, 0);

    // array.size = 2;
    // array.push(array.self, 0);

    // array.capacity = 70;
    // array.push(array.self, 0);

    // array.size = 70;
    // array.push(array.self, 0);

    // array.self = nullptr;
    // array.push(array.self, 0);

    // array.self = (stack*) 123;
    // array.push(array.self, 0);

    // array.name = "lox";
    // array.push(array.self, 0);

    return 0;
}
