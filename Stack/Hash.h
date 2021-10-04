//
// Created by Stas on 30.09.2021.
//

#ifndef STACK_HASH_H
#define STACK_HASH_H

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//{------------------------------------------------------------------------------------------------
/**
 * Hash calculation functions
 */

typedef uint64_t Hash_t;

/**
 * Permutation table which changes an input
 * hash using a certain rule
 * @param[in] index
 * @return new hash value
 */
Hash_t PermutationTable(Hash_t index);

/**
 * Calculates data hash using
 * modified Pearson's algorithm
 * @param[in] data
 * @param[in] dataSize
 * @return hash
 */
Hash_t CalculateHash(void* data, size_t dataSize);
//}------------------------------------------------------------------------------------------------

#endif //STACK_HASH_H
