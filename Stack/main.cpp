/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t(array);

    printf("hash %lld;\n", array.hash);

    for (int i = 0; i < 33; ++i) {
        array.push(array.self, i);
        printf("size %zd; capacity %zd; value %lf\n", array.size, array.capacity, array.top);
    }

    printf("\n\n");

    for (int i = 32; i >= 0; --i) {
        array.pop(array.self);
        printf("size %zd; capacity %zd; value %lf\n", array.size, array.capacity, array.top);
    }

    printf("hash %lld;\n", array.hash);

    StackDtor(&array);

    return 0;
}
