//
// Created by Stas on 30.09.2021.
//

#include "Hash.h"

Hash_t PermutationTable(Hash_t index)
{
    assert(index >= 0 && "Invalid Index");

    return index * 2 + 9;
}


Hash_t CalculateHash(void* data, size_t dataSize)
{
    assert(data && dataSize >= 0 && "Invalid Data");

    Hash_t* dataBuffer = nullptr;
    size_t  bufferSize = 0;

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

    int pos = 0;

    while (bufferSize > 0) {
        index = hash ^ dataBuffer[pos++];
        hash = PermutationTable(index);

        bufferSize -= sizeof (Hash_t);
    }

    free(dataBuffer);

    return hash;
}
