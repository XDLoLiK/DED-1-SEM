/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t(array); //!

//    array.push(array.self, 55);
//    printf("%llu\n", array.data[array.size - 1]);

//    int num = 0;
//
//    printf("%zd\n", CalculateHash(&num, sizeof num));

    for (int i = 0; i < 33; ++i) {
        array.push(array.self, i);
        printf("num %d; size %zd; capacity %zd; value %llu\n", i, array.size, array.capacity, array.top(array.self));
    }

    printf("\n\n");

    Location_t loc = __LOCATION__;
    array.dump(&array, "array", stdout, loc);

    printf("\n\n");

    for (int i = 33; i >= 1; --i) {
        array.pop(array.self);
        printf("size %zd; capacity %zd; value %llu\n", array.size, array.capacity, array.top(array.self));
    }

    StackDtor(&array);

    return 0;
}
