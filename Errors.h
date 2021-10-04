/**
 * @file Errors.h
 */

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


//}-------------------------------------------Error-codes------------------------------------------

enum ERROR_CODE {
    NO_ERROR                        = 0,
    INVALID_HASH                    = 1,
    POISON_NUMBER                   = 2,
    CAPACITY_ERROR                  = 3,
    POINTER_IS_NULL                 = 4,
    CANARY_ACCESSED                 = 5,
    ALLOCATION_ERROR                = 6,
    POISON_POINTER                  = 7,
    INITIALIZATION_ERROR            = 8,
    CAPACITY_DECREMENT_ERROR        = 9,
    CAPACITY_INCREMENT_ERROR        = 10,
    EMPTY_STACK_POP_ATTEMPT         = 11,
    EMPTY_STACK_TOP_ATTEMPT         = 12
};
//}------------------------------------------------------------------------------------------------
