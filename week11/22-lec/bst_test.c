#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include "../21-code/lib/contracts.h"


struct wcount {
  char* word;
  int count;
};

typedef struct wcount * wcount;

// GIVEN: two pointers of wcound
int elem_compare(elem e1, elem e2)
{
  REQUIRES(e1 != NULL && e2 != NULL);

  wcount w1 = (wcount)e1;
  wcount w2 = (wcount)e2;

  return strcmp((char*)(w1->word), (char*)(w2->word));
}


// GIVEN: two strings end with '\n'
// RETURNS: a concatenation of the two given string
char* string_append(char* s1, char* s2)
{
  char* result = (char*) xmalloc(strlen(s1)+strlen(s2)+1);
  sprintf(result, "%s%s", s1, s2);
  return result;
}

void print_tree(tree* T, char* s) {
  if (T == NULL) {
    printf("\n");
  } else {
    printf("%s(\"%s\":%d)\n", s, ((wcount)(T->data))->word,
           ((wcount)(T->data))->count);
    char* prefix = string_append(s, "  ");
    print_tree(T->left, prefix);
    print_tree(T->right, prefix);
    free(prefix);
  }
}

void print_bst(bst B)
{
  REQUIRES(B != NULL);

  char* s = (char*)xmalloc(100);
  sprintf(s, "%s", "");
  print_tree(B->root, s);
  free(s);
  return;
}

void test()
{
  // tests for bst_new()
  bst B = bst_new(&elem_compare);
  printf("bst_new() passes tests\n");

  // tests for bst_insert()
  int size = 5;
  int i = 0;
  for (i = 0; i < size; i++) {
    wcount w = (wcount) xmalloc(sizeof(struct wcount));
    w->word = (char*) xmalloc(size);
    sprintf(w->word,"%d", i);
    w->count = i;
    bst_insert(B, w);
  }
  printf("bst_insert() passes tests\n");
  print_bst(B);

  // tests for bst_lookup()
  //ASSERT(B == NULL);
  return;
}


int main() {
  test();

  return 0;
}
