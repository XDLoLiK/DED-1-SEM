/**
 * @file Errors.h
 */

#ifndef ERRORS_H
#define ERRORS_H

#include "Location.h"
#include <stdio.h>

//}------------------------------------------Error-logs--------------------------------------------

#define RETURN(ErrorName) {                                                                 \
                                                                                            \
    ERROR_LOG(ErrorName);                                                                   \
    return ErrorName;                                                                       \
}                                                                                           \
                                                                                            \
do {                                                                                        \
                                                                                            \
} while(0)


#define ERROR_LOG(ErrorName) {                                                              \
    Location_t location = __LOCATION__;                                                     \
                                                                                            \
    if ((ErrorName) != NO_ERROR) {                                                          \
        printf("\n=========================ERROR=OCCURRED!=======================\n\n");    \
        printf(">>> ERROR CODE: %d\n", ErrorName);                                          \
        printf(">>> REASON:     %s\n", #ErrorName);                                         \
        printf(">>> FILE:       %s\n", location.file);                                      \
        printf(">>> FUNCTION:   %s()\n", location.function);                                \
        printf(">>> LINE:       %d\n", location.line);                                      \
        printf("\n===============================================================\n\n");    \
    }                                                                                       \
}                                                                                           \
                                                                                            \
do {                                                                                        \
                                                                                            \
} while(0)

//}------------------------------------------------------------------------------------------------


//}------------------------------------------Error-codes-----------------------------------------------------

enum ERROR_CODE {

    // general errors
    NO_ERROR                        = 0,
    INVALID_HASH                    = 1,
    POISON_NUMBER                   = 2,
    CAPACITY_ERROR                  = 3,
    POINTER_IS_NULL                 = 4,
    ALLOCATION_ERROR                = 5,
    POISON_POINTER                  = 6,
    INITIALIZATION_ERROR            = 7,
    
    // stack errors
    CANARY_ACCESSED                 = 30,
    CAPACITY_DECREMENT_ERROR        = 31,
    CAPACITY_INCREMENT_ERROR        = 32,
    EMPTY_STACK_POP_ATTEMPT         = 33,
    EMPTY_STACK_TOP_ATTEMPT         = 34
};

//}------------------------------------------------------------------------------------------------


#endif // ERRORS_H
