/*
 * Unbounded priority queues interface, implemented as heaps
 * Smaller values are higher proirity, bigger values are higher priority
 * Currently doesn't shrink
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "xalloc.h"
#include "contracts.h"
#include "pq.h"

struct pq_header {
  size_t limit;                 /* limit = capacity+1 */
  size_t next;                  /* 1 <= next && next <= limit */
  pq_elem* data;                /* \length(data) == limit */
  unsigned int (*elem_priority)(pq_elem e);
  void (*elem_free)(pq_elem e);    
};
typedef struct pq_header* heap;

/* priority(H, i) returns priority of element i in H
 * it should not assume H is a heap */
inline static unsigned int priority(struct pq_header* H, size_t i) {
  REQUIRES(H != NULL);
  REQUIRES(1 <= i && i < H->next);
  REQUIRES(H->elem_priority != NULL);
  return (*H->elem_priority)(H->data[i]);
}

bool is_heap(struct pq_header* H) {
  if (!(H != NULL)) return false; 
  if (!(1 <= H->next && H->next <= H->limit)) return false;
  if (!(H->elem_priority != NULL)) return false;
  //@assert \length(H->data) == H->limit;
  for (size_t i = 2; i < H->next; i++)
    if (!(priority(H, i/2) <= priority(H, i))) return false;
  return true;
}

bool pq_empty(heap H) {
  REQUIRES(is_heap(H));
  return H->next == 1;
}

heap pq_new(size_t capacity,
            unsigned int (*elem_priority)(pq_elem e),
            void (*elem_free)(pq_elem e)) {
  REQUIRES(capacity > 0);
  heap H = xcalloc(1, sizeof(struct pq_header));      /* !! C !! */
  H->limit = capacity+1;
  H->next = 1;
  H->data = xcalloc(capacity+1, sizeof(pq_elem));          /* !! C !! */
  H->elem_priority = elem_priority;
  H->elem_free = elem_free;
  ENSURES(is_heap(H));
  return H;
}

void swap(pq_elem* A, size_t i, size_t j) {
  pq_elem tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

void pq_resize(heap H, size_t new_limit) {
  REQUIRES(is_heap(H));
  
  pq_elem *new_data = xcalloc(new_limit, sizeof(pq_elem));

  for (size_t i = 0; i < H->next; i++) 
    new_data[i] = H->data[i];

  free(H->data);
  H->limit = new_limit;
  H->data = new_data;
}

void pq_insert(heap H, pq_elem e) {
  REQUIRES(is_heap(H));

  if (H->next == H->limit) {
    assert(H->limit < UINT_MAX/2);
    pq_resize(H, 2*H->limit);
  }
  ASSERT(H->next < H->limit);

  H->data[H->next] = e;
  (H->next)++;
  /* sift up to restore invariant */
  size_t i = H->next - 1;
  while (i > 1 && priority(H,i) < priority(H,i/2))
    {
      swap(H->data, i, i/2);
      i = i/2;
    }
  ENSURES(is_heap(H));
  return;
}

void sift_down(heap H, size_t i) {
  REQUIRES(1 <= i && i < H->next);
  size_t n = H->next;
  size_t left = 2*i;
  size_t right = left+1;
  while (left < n) {
    if (priority(H,i) <= priority(H,left)
        && (right >= n || priority(H,i) <= priority(H,right)))
      return;
    if (right >= n || priority(H,left) < priority(H,right)) {
      swap(H->data, i, left);
      i = left;
    } else {
      swap(H->data, i, right);
      i = right;
    }
    left = 2*i;
    right = left+1;
  }
  ENSURES(is_heap(H));
  return;
}

pq_elem pq_delmin(heap H) {
  REQUIRES(is_heap(H));
  REQUIRES(!pq_empty(H));
  size_t n = H->next;
  pq_elem min = H->data[1];
  H->data[1] = H->data[n-1];
  H->next = n-1;
  H->data[n-1] = NULL;		/* delete reference to element */
  if (H->next > 1) sift_down(H, 1);
  ENSURES(is_heap(H));
  return min;
}

pq_elem pq_min(heap H) {
  REQUIRES(is_heap(H));
  REQUIRES(!pq_empty(H));

  return H->data[1];
}

void pq_free(heap H) {
  REQUIRES(is_heap(H));

  if (H->elem_free != NULL) {
    for (size_t i = 1; i < H->limit; i++) {
      (*H->elem_free)(H->data[i]);
    }
  }

  free(H->data);
  free(H);
  return;
}
