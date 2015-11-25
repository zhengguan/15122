/*
 * Unbounded priority queues interface
 * Smaller values are higher proirity, bigger values are higher priority
 * Unsigned, so 0 is the highest priority.
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _PQ_H_
#define _PQ_H_

typedef void *pq_elem; // NULL vs. non-NULL is not significant

typedef struct pq_header* pq;

pq pq_new(size_t capacity,                            // Must be > 0
          unsigned int (*elem_priority)(pq_elem e),   // Must not be NULL
          void (*elem_free)(pq_elem e));              // May be NULL 

bool pq_empty(pq P);
void pq_insert(pq P, pq_elem e);
pq_elem pq_min(pq P);    /* P must not be empty */
pq_elem pq_delmin(pq P); /* P must not be empty */
void pq_free(pq P);

#endif
