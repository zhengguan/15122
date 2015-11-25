#include <stdio.h>

#include "./lib/contracts.h"
#include "tst.h"
#include "queue.h"

void Queue_print(Queue q) {
  for (size_t i = 0; i < q->len; i++) {
    printf("The %dth element of queue is: %s\n", i, q->buf[i]);
  }
  return;
}

void array_dealloc(void **elems, size_t len) {
  for (size_t i = 0; i < len; i++) {
    free(elems[i]);
  }
  free(elems);
  return;
}

void test_case_tst_member_generalized(tst T, char *pattern) {
  Queue q = Queue_new();
  tst_member_generalized(T, pattern, q);
  printf("\nstring \"%s\" matches:\n", pattern);
  Queue_print(q);
  array_dealloc((void **)Queue_dealloc(q), q->len);
  return;
}

void test() {
  printf("Entering tests\n");

  // tests for tst_new()
  tst T = tst_new();
  printf("tst_new() passes tests\n");

  // tests for tst_insert()
  tst_insert(T, "ab");
  tst_insert(T, "abc");

  printf("height is %d\n", T->root->height);

  tst_insert(T, "de");
  tst_insert(T, "ghi");
  printf("The root node is %s\n", (char*)((tree*)T->root)->data);

  ASSERT(*(char*)T->root->data == 'd');
  printf("tst_insert() passes tests\n");

  // tests for tst_lookup()
  ASSERT(tst_lookup(T, "ab") == 1);
  ASSERT(tst_lookup(T, "a") == 0);
  ASSERT(tst_lookup(T, "abc") == 1);
  ASSERT(tst_lookup(T, "abcd") == 0);
  printf("tst_lookup() passes tests\n");

  tst_free(T);
  printf("tst_free() passes teests\n");
  // tests for tst_member_generalized(0
  T = tst_new();
  tst_insert(T, "a");
  tst_insert(T, "b");
  tst_insert(T, "c");
  tst_insert(T, "bd");
  tst_insert(T, "be");

  Queue q = Queue_new();
  tst_member_generalized(T, "*", q);  printf("I am here.\n");
  printf("\nstring \"%s\" matches:\n", "*");
  Queue_print(q);
  array_dealloc((void **)Queue_dealloc(q), q->len);


  q = Queue_new();
  char *pattern = "b*";
  tst_member_generalized(T, pattern, q);
  printf("\nstring \"%s\" matches:\n", pattern);
  Queue_print(q);
  array_dealloc((void **)Queue_dealloc(q), q->len);


  tst_insert(T, "bdf");
  tst_insert(T, "bdg");
  test_case_tst_member_generalized(T, "*d*");
  test_case_tst_member_generalized(T, "bd*");

  tst_free(T);

  T = tst_new();
  tst_insert(T, "d");
  tst_insert(T, "df");
  tst_insert(T, "dg");
  test_case_tst_member_generalized(T, "d*");

  tst_free(T);

  printf("tst_free() passes tests\n");
  return;
}


int main() {
  test();
  return 0;
}
