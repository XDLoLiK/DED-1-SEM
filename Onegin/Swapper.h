/**
 * @file Swapper.h
 */

#ifndef SWAPPER_H
#define SWAPPER_H

#include <inttypes.h>
#include <assert.h>
#include <string.h>

//{------------------------------------------------------------------------------------------------
/**
 * Template for swap_<size> functions
 */
#define DEF_SWAP(type)                                                           \
                                                                                 \
    void swap##_##type (void** firstElem, void** secondElem, size_t* elemSize) { \
                                                                                 \
    while (*elemSize >= sizeof (type)) {                                         \
        type buffer = *((type*) (*firstElem));                                   \
        *((type*) (*firstElem)) = *((type*) (*secondElem));                      \
        *((type*) (*secondElem)) = buffer;                                       \
                                                                                 \
        *elemSize -= sizeof (type);                                              \
                                                                                 \
        *firstElem = (type*) (*firstElem) + 1;                                   \
        *secondElem = (type*) (*secondElem) + 1;                                 \
    }                                                                            \
}

//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Swaps two strings' pointers in the list
 * @param[in,out] firstString pointer to the first element
 * @param[in,out] secondString pointer to the second element
 * @param[in] elemSize size of 1 element
 */
void swapElements(void* firstElem, void* secondElem, size_t elemSize);
//}------------------------------------------------------------------------------------------------

#endif //SWAPPER_H
