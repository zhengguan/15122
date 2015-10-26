#include <string.h>
#include <malloc.h>

char* reverse(char* s)
{
  int len = strlen(s);
  char* result = (char*) malloc(len*sizeof(char)+1);
  int i;
  for (i = 0; i < len; i++)
    //@loop_invariant 0 <= i;
    {
      //@assert i < len;
      result[i] = s[len-1-i];
    }
  result[i] = '\0';
  return result;
}


int main()
{
  char* s = reverse("hello, world!");
  printf("%p\n", s);

  printf("%s\n",s);
  free(s);
  s = NULL;
  printf("%p\n", s);
  return 0;
}
