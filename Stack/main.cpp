/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t(array); 

    // int num = 0;
    // printf("%zd\n", CalculateHash(&num, sizeof num));

    array.push(array.self, 1);
    printf("%llu\n", array.top(array.self));
    array.push(array.self, 2);
    printf("%llu\n", array.top(array.self));
    array.push(array.self, 3);
    printf("%llu\n", array.top(array.self));
    array.push(array.self, 4);
    printf("%llu\n", array.top(array.self));
    array.push(array.self, 5);
    printf("%llu\n", array.top(array.self));
    array.push(array.self, 6);
    printf("%llu\n", array.top(array.self));


    for (int i = 0; i < 33; ++i) {
        array.push(array.self, i);
        printf("num %d; size %zd; capacity %zd; value %llu\n", i, array.size, array.capacity, array.top(array.self));
    }

    printf("\n\n");

    for (int i = 32; i >= 1; --i) {
        array.pop(array.self);
        printf("num %d; size %zd; capacity %zd; value %llu\n", i, array.size, array.capacity, array.top(array.self));
    }

    StackDtor(array.self);

    return 0;
}
