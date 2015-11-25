/*
 * Hash sets interface
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _HSET_H_
#define _HSET_H_

typedef void *hset_elem;
typedef bool elem_equal_fn(hset_elem x, hset_elem y);
typedef size_t elem_hash_fn(hset_elem x);
typedef void elem_free_fn(hset_elem x);

typedef struct hset_header* hset;

hset hset_new(size_t capacity,           // Must be > 0
              elem_equal_fn *elem_equal, // Must be non-NULL
              elem_hash_fn *elem_hash,   // Must be non-NULL
              elem_free_fn *elem_free);  // May be NULL

hset_elem hset_insert(hset H, hset_elem x);

hset_elem hset_lookup(hset H, hset_elem x);

void hset_free(hset H);

#endif
