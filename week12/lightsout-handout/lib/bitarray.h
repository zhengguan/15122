/*
 * Bit arrays - fixed-width arrays of bits w/ a toggle function
 * 
 * Bit arrays must be unsigned integer types (meaning that bitarrays
 * can be compared for equality using x == y) and should contain at
 * least BITARRAY_LIMIT bits.
 *
 * Both implementations and clients should allow for different
 * BITARRAY_LIMIT values and different unsigned integer types to be
 * used.
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdint.h>

#ifndef _BITARRAY_H_
#define _BITARRAY_H_

typedef uint32_t bitarray;

#define BITARRAY_LIMIT 25

/* Get a new bitarray with everything set to 'false' */
bitarray bitarray_new();

/* Get the ith bit of the bitarray n */
bool bitarray_get(bitarray n, uint8_t i); // 0 <= i < BITARRAY_LIMIT

/* Toggle the ith bit of the bitarray n, returning a new bitarray */
/* The old bitarray remains unchanged (this is a persistent data structure) */
bitarray bitarray_flip(bitarray n, uint8_t i); // 0 <= i < BITARRAY_LIMIT

#endif
