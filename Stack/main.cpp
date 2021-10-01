/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t(array);

    printf("hash %lld;\n", *array.stackHash);

    for (int i = 0; i < 33; ++i) {
        array.push(array.self, i);
        printf("size %zd; capacity %zd; value %llu\n", array.size, array.capacity, array.top);
    }

    printf("\n\n");

    Location_t loc = __LOCATION__;
    array.dump(&array, "array", stdout, loc);

    printf("\n\n");

    for (int i = 32; i >= 0; --i) {
        array.pop(array.self);
        printf("size %zd; capacity %zd; value %llu\n", array.size, array.capacity, array.top);
    }

    printf("hash %lld;\n", *array.stackHash);

    StackDtor(&array);

    return 0;
}
