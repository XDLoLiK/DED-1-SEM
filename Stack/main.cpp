#include "stdio.h"
#include "Logger.h"
#include "Stack.h"

const char* LOG_FILENAME = "stack.log";

int main(){
    Stack stack = {};

    stack_init(&stack);

    STACK_DUMP(&stack);
    
    stack_free(&stack);
    stack_free(&stack);

    return 0;
}
