#include <stdlib.h>
#include "lib/bitarray.h"
#include "lib/xalloc.h"
#include "lib/contracts.h"

// Interface

/* Get a new bitarray with everything set to 'false' */
bitarray bitarray_new();

/* Get the ith bit of the bitarray n */
bool bitarray_get(bitarray n, uint8_t i); // 0 <= i < BITARRAY_LIMIT

/* Toggle the ith bit of the bitarray n, returning a new bitarray */
/* The old bitarray remains unchanged (this is a persistent data structure) */
bitarray bitarray_flip(bitarray n, uint8_t i); // 0 <= i < BITARRAY_LIMIT

// Implementation

bitarray bitarray_new() {
  //  bitarray *ba = xcalloc(1, sizeof(bitarray));
  //  return *ba;
  return (bitarray) 0;
}


bool bitarray_get(bitarray n, uint8_t i) {
  REQUIRES(i < BITARRAY_LIMIT);

  return (((n >> i) & 1) == 1);
}

bitarray bitarray_flip(bitarray n, uint8_t i) {
  REQUIRES(i < BITARRAY_LIMIT);

  //  bitarray *ba = bitarray_new();
  //  *ba = n;
  bitarray mask = 1 << i;
  return n ^ mask;
}
