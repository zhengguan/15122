#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "lib/contracts.h"
#include "lib/bitarray.h"


// test functions of bitarray
void test_bitarray() {
  // tests for bitarray_new()
  bitarray b1 = bitarray_new();
  ASSERT(b1 == 0);

  // tests for bitarray_flip()
  bitarray b2 = bitarray_flip(b1, BITARRAY_LIMIT - 1);
  bitarray b3 = bitarray_flip(b1, 0);

  // tests for bitarray_get()
  ASSERT(bitarray_get(b1, BITARRAY_LIMIT - 1) == false);
  ASSERT(bitarray_get(b2, BITARRAY_LIMIT - 1) == true);
  ASSERT(bitarray_get(b1, 0) == false);
  ASSERT(bitarray_get(b3, 0) == true);

  return;
}


int main() {
  test_bitarray();
  return 0;
}
