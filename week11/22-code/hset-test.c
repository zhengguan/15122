/*
 * Testing hash tables (unit tests and randomized tests)
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "hset.h"

/******************************/
/* Client-side implementation */
/******************************/

size_t elem_hash(elem x) {
  REQUIRES(x != NULL);
  int a = *(int*)x;
  size_t b = (size_t)(unsigned int)a;
  size_t h = b*1664525 + 1013904223;
  return h;
}

bool elem_equal(elem x, elem y) {
  REQUIRES(x != NULL && y != NULL);
  return *(int*)x == *(int*)y;
}

void elem_free(elem x) {
  free(x);
}

/****************/
/* Testing code */
/****************/

elem elem_fromint(int i) {
  int* x = xmalloc(sizeof(int));
  *x = i;
  return (void*)x;
}

int main() {
  int i;
  elem E1 = elem_fromint(42);
  elem E2 = elem_fromint(115);
  elem E3 = elem_fromint(42);
  elem E4 = elem_fromint(-215);

  hset H = hset_new(3, &elem_equal, &elem_hash, &elem_free);
  assert(H != NULL);
  i = 0;   assert(hset_lookup(H, (void*)&i) == NULL);
  i = 115; assert(hset_lookup(H, (void*)&i) == NULL);

  free(hset_insert(H, elem_fromint(98)));
  free(hset_insert(H, elem_fromint(88)));
  free(hset_insert(H, elem_fromint(14)));
  free(hset_insert(H, elem_fromint(67)));
  free(hset_insert(H, elem_fromint(23)));
  free(hset_insert(H, elem_fromint(-12)));
  free(hset_insert(H, elem_fromint(39)));
  
  free(hset_insert(H, E1));
  i = 42;   assert(hset_lookup(H, (void*)&i) == E1);
  i = 115;  assert(hset_lookup(H, (void*)&i) == NULL);
  i = -215; assert(hset_lookup(H, (void*)&i) == NULL);
  i = 0;    assert(hset_lookup(H, (void*)&i) == NULL);
  
  free(hset_insert(H, E2));
  i = 42;   assert(hset_lookup(H, (void*)&i) == E1);
  i = 115;  assert(hset_lookup(H, (void*)&i) == E2);
  i = -215; assert(hset_lookup(H, (void*)&i) == NULL);
  i = 0;    assert(hset_lookup(H, (void*)&i) == NULL);

  free(hset_insert(H, E3));
  i = 42;   assert(hset_lookup(H, (void*)&i) == E3);
  i = 115;  assert(hset_lookup(H, (void*)&i) == E2);
  i = -215; assert(hset_lookup(H, (void*)&i) == NULL);
  i = 0;    assert(hset_lookup(H, (void*)&i) == NULL);

  free(hset_insert(H, E4));
  i = 42;   assert(hset_lookup(H, (void*)&i) == E3);
  i = 115;  assert(hset_lookup(H, (void*)&i) == E2);
  i = -215; assert(hset_lookup(H, (void*)&i) == E4);
  i = 0;    assert(hset_lookup(H, (void*)&i) == NULL);
  
  printf("Running some sequential entries\n");
  for(int k = 0; k < 20; k = k+2) {
    elem x = elem_fromint(k);
    free(hset_insert(H, x));
    assert(hset_lookup(H, (void*)&k) == x);
  }

  for(int k = 0; k > -20; k = k-2) {
    free(hset_insert(H, elem_fromint(k)));
  }

  for (int k = -19; k < 20; k++) {
    if (k % 2 == 0) assert(hset_lookup(H, (void*)&k) != NULL);
    else assert(hset_lookup(H, (void*)&k) == NULL);
  }
  
  printf("Running some random entries\n");
  for (int k = 0; k < 5000; k++) {
    int r = rand();
    elem x = elem_fromint(r);
    free(hset_insert(H, x));
    assert(hset_lookup(H, (void*)&r) == x);
  }
      
  hset_free(H);

  printf("Tests passed!\n");
  return 0;
}
