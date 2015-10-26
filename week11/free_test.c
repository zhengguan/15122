#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>




int main()
{
  int * arr = (int*) malloc(10*sizeof(int));
  int * p = arr + 3;
  unsigned char c = 0xF0;
  int i = (int)c;
  printf("i = %x\n", i);
  assert(i == 240);

  signed short ss = -1;
  unsigned short us = 1;


  char* y = "hello!";
  char* x = (char*) malloc(7*sizeof(char));
  strncpy(x, y, strlen(y));
  printf("length of x is %zu\n", strlen(x));
  free(x);
  return 0;
}
