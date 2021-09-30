//
// Created by Stas on 30.09.2021.
//

#ifndef STACK_HASH_H
#define STACK_HASH_H

#include <inttypes.h>
#include <assert.h>
#include <string.h>

typedef uint64_t Hash_t;

Hash_t PermutationTable(Hash_t index);
Hash_t CalculateHash(void* data, size_t dataSize);

#endif //STACK_HASH_H
