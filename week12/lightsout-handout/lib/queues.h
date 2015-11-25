/* 
 * Queues 
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>

#ifndef _QUEUES_H_
#define _QUEUES_H_

typedef void *queue_elem;
typedef struct queue_header* queue;
bool queue_empty(queue Q);           /* O(1) */
queue queue_new();                   /* O(1) */
void enq(queue Q, queue_elem e);     /* O(1) */
queue_elem deq(queue Q);             /* O(1) */

/* If the second argument is non-NULL, then  *
 * the elem_free function will be run on     *
 * every element still in the queue. If the  * 
 * second argument is NULL, the elem_free    *
 * function won't be run.                    */
void queue_free(queue Q, void (*elem_free)(queue_elem e));

#endif
