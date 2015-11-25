#include "queue.h"

bool is_Queue(Queue q) {
  return (q != NULL) && (q->buf != NULL) && (q->len <= q->limit);
}

Queue Queue_new() {
  Queue q = xcalloc(1, sizeof(struct queue));
  q->buf = xcalloc(1, sizeof(Queue_elem));
  q->len = 0;
  q->limit = 1;
  return q;
}

// EFFECT: free the given Queue
// RETURNS: all elements in the given queue as an array
Queue_elem* Queue_dealloc(Queue q) {
  REQUIRES(is_Queue(q));

  Queue_elem *buf = q->buf;
  free(q);
  return buf;
}
void Queue_insert(Queue q, Queue_elem ele) {
  REQUIRES(is_Queue(q));
  REQUIRES(ele != NULL);

  if (q->len == q->limit) {
    Queue_elem *buf = xcalloc(q->limit * 2, sizeof(Queue_elem));
    memcpy(buf, q->buf, q->len * sizeof(Queue_elem));
    free(q->buf);
    q->buf = buf;
    q->limit = q->limit * 2;
  }
  q->buf[q->len++] = ele;

  ENSURES(is_Queue(q));
}
