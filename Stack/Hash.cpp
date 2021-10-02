//
// Created by Stas on 30.09.2021.
//

#include "Hash.h"

Hash_t PermutationTable(Hash_t index)
{
    assert(index >= 0 && "Invalid Index");

    Hash_t maxIndex = 1;

    /// Max Hash_t value size is 2^64 - 1 which 
    /// is also 2^63 - 1 + 2^63 (to avoid overflow)
    for (int i = 0; i < 62; ++i) {
        maxIndex *= 2;
    }

    maxIndex = maxIndex - 1 + maxIndex;

    return maxIndex - index;
}

Hash_t CalculateHash(void* data, size_t dataSize)
{
    assert(data && dataSize >= 0 && "Invalid Data");

    Hash_t * dataBuffer = nullptr;
    size_t bufferSize = 0;

    /// Extending the data size to the minimal data size
    if (dataSize < sizeof (Hash_t))
        bufferSize = sizeof (Hash_t) * 2;
    else if (dataSize >= sizeof (Hash_t))
        bufferSize = (sizeof (Hash_t) - dataSize % sizeof (Hash_t)) % sizeof (Hash_t) + dataSize;

    /// Creating a buffer for the data to not spoil it
    dataBuffer = (Hash_t*) calloc(1, bufferSize);
    memcpy(dataBuffer, data, bufferSize);

    dataBuffer[bufferSize / sizeof (Hash_t) - 1] += 1;

    Hash_t hash = 0;
    Hash_t index = 0;

    while (bufferSize > 0) {
        index = hash ^ *dataBuffer;
        hash = PermutationTable(index);

        bufferSize -= sizeof (Hash_t);
        dataBuffer += 1;
    }

    return hash;
}
