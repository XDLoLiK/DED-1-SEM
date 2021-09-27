/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Stack.h"

int main(void)
{
    Stack_t(array);

    array.push(array.self, 1);
    printf("%lf\n", array.data[array.size - 1]);

    array.push(array.self, 6);
    printf("%lf\n", array.data[array.size - 1]);

    array.pop(array.self);
    printf("%lf\n", array.data[array.size - 1]);

    return 0;
}