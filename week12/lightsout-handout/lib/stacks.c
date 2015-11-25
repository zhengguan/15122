/* 
 * Stacks 
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>
#include "xalloc.h"
#include "contracts.h"
#include "stacks.h"

/* Aux structure of linked lists */
struct list_node {
  stack_elem data;
  struct list_node* next;
};
typedef struct list_node list;

/* will diverge if list is circular! */
static bool is_stack_segment(list* start, list* end)
{
  list *p = start;
  while (p != end) {
    if (p == NULL) return false;
    p = p->next;
  }
  return true;
}

/* Stacks */ 

struct stack_header {
  list *top;
  list *bottom;
};

bool is_stack (stack S) {
  if (S == NULL) return false;
  if (S->top == NULL || S->bottom == NULL) return false;
  if (!is_stack_segment(S->top, S->bottom)) return false;
  return true;
}

bool stack_empty(stack S) {
  REQUIRES(is_stack(S));
  return S->top == S->bottom;
}

stack stack_new() {
  stack S = xmalloc(sizeof(struct stack_header));
  list *p = xmalloc(sizeof(struct list_node));
  /* Dummy node: does not need to be initialized! */
  S->top = p;
  S->bottom = p;
  ENSURES(is_stack(S));
  ENSURES(stack_empty(S));
  return S;
}

void push(stack S, stack_elem e) {
  REQUIRES(is_stack(S));

  list *first = xmalloc(sizeof(struct list_node));
  first->data = e;
  first->next = S->top;
  S->top = first;

  ENSURES(is_stack(S) && !stack_empty(S));
}

stack_elem pop(stack S) {
  REQUIRES(is_stack(S));
  REQUIRES(!stack_empty(S));

  stack_elem e = S->top->data;  /* save old stack element to return */
  list* q = S->top;             /* save old list node to free */
  S->top = S->top->next;
  free(q);                      /* free old list node */

  ENSURES(is_stack(S));
  return e;                     /* return old stack element */
}

void stack_free(stack S, void (*elem_free)(stack_elem e)) {
  REQUIRES(is_stack(S));

  while (S->top != S->bottom) {
    ASSERT(is_stack_segment(S->top, S->bottom));
    list* p = S->top;
    if (elem_free != NULL) (*elem_free)(p->data);
    S->top = S->top->next;
    free(p);
  }

  free(S->top); /* == S->bottom */
  free(S);
}
