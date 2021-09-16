/**
 * Swapper.cpp
 */

#include "Swapper.h"

void swapElements(void* firstElem, void* secondElem, size_t elemSize) // have to think about size. >1kb ??? //!
{
    assert(firstElem != nullptr);
    assert(secondElem != nullptr);

    while (elemSize > 0) {
        swap64(&firstElem, &secondElem, &elemSize);
        swap32(&firstElem, &secondElem, &elemSize);
        swap16(&firstElem, &secondElem, &elemSize);
        swap8(&firstElem, &secondElem, &elemSize);
    }
}

void swap8(void** firstElem, void** secondElem, size_t* elemSize) //! copypast
{
    while (*elemSize >= 1) {
        uint8_t buffer = *((uint8_t*) (*firstElem));
        *((uint8_t*) (*firstElem)) = *((uint8_t*) (*secondElem));
        *((uint8_t*) (*secondElem)) = buffer;

        *elemSize -= 1;

        *firstElem = (uint8_t*) (*firstElem) + 1;
        *secondElem = (uint8_t*) (*secondElem) + 1;
    }
}

void swap16(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 2) {
        uint16_t buffer = *((uint16_t*) (*firstElem));
        *((uint16_t*) (*firstElem)) = *((uint16_t*) (*secondElem));
        *((uint16_t*) (*secondElem)) = buffer;

        *elemSize -= 2;

        *firstElem = (uint16_t*) (*firstElem) + 1;
        *secondElem = (uint16_t*) (*secondElem) + 1;
    }
}

void swap32(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 4) {
        uint32_t buffer = *((uint32_t*) (*firstElem));
        *((uint32_t*) (*firstElem)) = *((uint32_t*) (*secondElem));
        *((uint32_t*) (*secondElem)) = buffer;

        *elemSize -= 4;

        *firstElem = (uint32_t*) (*firstElem) + 1;
        *secondElem = (uint32_t*) (*secondElem) + 1;
    }
}

void swap64(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 8) {
        uint64_t buffer = *((uint64_t*) (*firstElem));
        *((uint64_t*) (*firstElem)) = *((uint64_t*) (*secondElem));
        *((uint64_t*) (*secondElem)) = buffer;

        *elemSize -= 8;

        *firstElem = (uint64_t*) (*firstElem) + 1;
        *secondElem = (uint64_t*) (*secondElem) + 1;
    }
}
