/*
 * Hash sets implementation
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "hset.h"

struct chain_node {
  elem data;
  struct chain_node* next;
};
typedef struct chain_node chain;

struct hset_header {
  size_t size;
  size_t capacity;               /* 0 < capacity */
  chain **table;             /* \length(table) == capacity */
  elem_equal_fn *elem_equal;
  elem_hash_fn *elem_hash;
  elem_free_fn *elem_free;
};

static inline size_t hashindex(hset H, elem x) {
  REQUIRES(H != NULL && H->capacity > 0 && H->elem_hash != NULL);
  return (*H->elem_hash)(x) % H->capacity;
}

static inline bool elemequal(hset H, elem x, elem y) {
  REQUIRES(H != NULL && H->capacity > 0 && H->elem_equal != NULL);
  return (*H->elem_equal)(x, y);
}

static bool is_chain(hset H, chain* p, size_t i) {
  REQUIRES (H != NULL && H->capacity > 0 && H->elem_hash != NULL);
  if (p == NULL) return true;
  return p->data != NULL 
    && hashindex(H, p->data) == i
    && is_chain(H, p->next, i);
}

static bool is_chains(hset H, size_t lo, size_t hi) {
  REQUIRES(H != NULL && H->capacity > 0 && H->elem_hash != NULL);
  REQUIRES(lo <= hi && hi <= H->capacity);
  if (lo == hi) return true;
  return is_chain(H, H->table[lo], lo) 
    && is_chains(H, lo+1, hi);
}

bool is_hset(hset H) {
  return  H != NULL
    && H->capacity > 0
    && H->elem_equal != NULL
    && H->elem_hash != NULL
    && is_chains(H, 0, H->capacity);
}

hset hset_new(size_t capacity,  
              elem_equal_fn *elem_equal,
              elem_hash_fn *elem_hash, 
              elem_free_fn *elem_free) {
  REQUIRES(capacity > 0 && elem_equal != NULL && elem_hash != NULL);

  hset H = xmalloc(sizeof(struct hset_header));
  H->size = 0;
  H->capacity = capacity;
  H->table = xcalloc(capacity, sizeof(chain*));
  H->elem_equal = elem_equal;
  H->elem_hash = elem_hash;
  H->elem_free = elem_free;

  ENSURES(is_hset(H));
  return H;
}

elem hset_lookup(hset H, elem x) {
  REQUIRES(is_hset(H) && x != NULL);
  
  int i = hashindex(H, x);
  for (chain* p = H->table[i]; p != NULL; p = p->next) {
    if (elemequal(H, p->data, x)) {
      return p->data;
    }
  }

  return NULL;
}

elem hset_insert(hset H, elem x) {
  REQUIRES(is_hset(H) && x != NULL);
  
  int i = hashindex(H, x);
  for (chain* p = H->table[i]; p != NULL; p = p->next) {
    if (elemequal(H, p->data, x)) {
      elem old = p->data;
      p->data = x;
      return old;
    }
  }
  
  // prepend new element
  chain* p = xmalloc(sizeof(chain));
  p->data = x;
  p->next = H->table[i];
  H->table[i] = p;
  (H->size)++;

  ENSURES(is_hset(H));
  return NULL;
}

void hset_free(hset H) {
  REQUIRES(is_hset(H));

  for (size_t i = 0; i < H->capacity; i++) {
    chain* p_next;
    for (chain* p = H->table[i]; p != NULL; p = p_next) {
      if (H->elem_free != NULL) (*H->elem_free)(p->data);
      p_next = p->next;
      free(p);
    }
  }

  free(H->table);
  free(H);
}
