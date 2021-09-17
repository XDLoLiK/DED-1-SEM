/**
 * @file Swapper.cpp
 */

#include "Swapper.h"

DEF_SWAP(uint8_t)
DEF_SWAP(uint16_t)
DEF_SWAP(uint32_t)
DEF_SWAP(uint64_t)

void swapElements(void* firstElem, void* secondElem, size_t elemSize)
{
    assert(firstElem != nullptr);
    assert(secondElem != nullptr);

    // if object's size is bigger than 1Kb
    if (elemSize >= 1024) {
        void* temporary = calloc(1, elemSize);

        memcpy(temporary, firstElem, elemSize);
        memcpy(firstElem, secondElem, elemSize);
        memcpy(secondElem, temporary, elemSize);
    }
    // if object's size isn't that big
    else {
        while (elemSize > 0) {
            swap_uint64_t(&firstElem, &secondElem, &elemSize);
            swap_uint32_t(&firstElem, &secondElem, &elemSize);
            swap_uint16_t(&firstElem, &secondElem, &elemSize);
            swap_uint8_t(&firstElem, &secondElem, &elemSize);
        }
    }
}
