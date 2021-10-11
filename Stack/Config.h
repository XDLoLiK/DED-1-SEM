/**
* @file StackConfig.h
*/

#ifndef CONFIG_H
#define CONFIG_H

typedef uint64_t StackElem_t;
typedef size_t   Canary_t;


#define VALIDATION_INACTIVE


#ifdef VALIDATION_ACTIVE
    #define ON_DEBUG(expr) expr
#else
    #define ON_DEBUG(expr)
#endif


//{--------------------------------Validation-levels-----------------------------------------------

enum ValidationDepth {
    NO_VALIDATION = 0,      /// does no validation
    EASY          = 1,      /// checks only stack's fields
    MEDIUM        = 2,      /// checks canaries
    HARD          = 3       /// checks hashes
};

#define VALIDATION_DEPTH HARD

//}------------------------------------------------------------------------------------------------


#endif // CONFIG_H
