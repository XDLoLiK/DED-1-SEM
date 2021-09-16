/**
 * @file Swapper.h
 */

#ifndef SWAPPER_H
#define SWAPPER_H

#include <inttypes.h>
#include <assert.h>

//{------------------------------------------------------------------------------------------------
/**
 * A "family" of swap n bytes functions
 */

/**
 * Swaps 8 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */
void swap8(void** firstElem, void** secondElem, size_t* elemSize);

/**
 * Swaps 16 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */
void swap16(void** firstElem, void** secondElem, size_t* elemSize);

/**
 * Swaps 32 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */
void swap32(void** firstElem, void** secondElem, size_t* elemSize);

/**
 * Swaps 64 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */
void swap64(void** firstElem, void** secondElem, size_t* elemSize);

/**
 * Swaps two strings' pointers in the list
 * @param[in,out] firstString pointer to the first element
 * @param[in,out] secondString pointer to the second element
 * @param[in] elemSize size of 1 element
 */
void swapElements(void* firstElem, void* secondElem, size_t elemSize);
//}------------------------------------------------------------------------------------------------

#endif //SWAPPER_H
