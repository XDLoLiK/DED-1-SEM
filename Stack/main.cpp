/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t (array); 

    array.dump(array.self, "array", stdout, __LOCATION__);

    array.push(array.self, 1);
    
    array.dump(array.self, "array", stdout, __LOCATION__);

    int num = 0;
    printf("%zd\n", CalculateHash(&num, sizeof num));

    printf("Hash %zd;\n", array.hash);    

    for (int i = 0; i < 32; ++i) {
        array.push(array.self, i);
        // printf("num %d; size %zd; capacity %zd; value %llu\n", i, array.size, array.capacity, array.top(array.self));
    }

    printf("Hash %zd;\n", array.hash);
    printf("\n\n");

    for (int i = 32; i >= 0; --i) {
        array.pop(array.self);
        // printf("num %d; size %zd; capacity %zd; value %llu\n", i, array.size, array.capacity, array.top(array.self));
    }

    printf("%llu\n", array.top(array.self));

    printf("Hash %zd;\n", array.hash);

    array.hash = 1;

    array.push(array.self, 1);

    StackDtor(array.self);
    StackDtor(array.self);

    return 0;
}
