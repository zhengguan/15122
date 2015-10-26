/*
 * Hash sets interface
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _HSET_H_
#define _HSET_H_

typedef void *elem;
typedef bool elem_equal_fn(elem x, elem y);
typedef size_t elem_hash_fn(elem x);
typedef void elem_free_fn(elem x);

typedef struct hset_header* hset;

hset hset_new(size_t capacity,           // Must be > 0
              elem_equal_fn *elem_equal, // Must be non-NULL
              elem_hash_fn *elem_hash,   // Must be non-NULL
              elem_free_fn *elem_free);  // May be NULL

elem hset_insert(hset H, elem x);

elem hset_lookup(hset H, elem x);

void hset_free(hset H);

#endif
