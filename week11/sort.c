#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./21-code/lib/xalloc.h"

typedef int compare_fn(void *x, void *y);

int string_compare(void* s1, void* s2) {
  return strcmp((char*)s2, (char*)s1);
}

int int_compare(void* i1, void* i2) {
  return *(int*) i1 - *(int*)i2;
}

int main()
{
  compare_fn *cmp = &string_compare;
  void** S = xcalloc(4, sizeof(void*));
  //  S[0] = (void*)"pancake";
  //  S[1] = (void*)"waffle";
  //  S[2] = (void*)"toast";
  //  S[3] = (void*)"juice";
  S[0] = "aee\0";
  S[1] = "bee\0";
  S[2] = "dee\0";
  S[3] = "cee\0";


  //  qsort(S, sizeof(S), sizeof(S[0]), &string_compare);
  qsort(S, 4, sizeof(S[0]), strcmp);


  int i;
  for (i = 0; i < 3; i++) {
    printf("string_compare(S[%d],S[%d]) is %d.\n",
           i, i+1, strcmp(S[i], S[i+1]));
  }

  for (i = 0; i < 4; i++) {
    printf("%s\n", (char*)S[i]);
  }
  printf("\n");

  int arr[4];
  for (i = 0; i < 4; i++) {
    arr[i] = 4 - i;
  }
  qsort((void*)arr,4, sizeof(int), &int_compare);
  for (i = 0; i < 4; i++) {
    printf("%d\n", arr[i]);
  }

  return 0;
}
