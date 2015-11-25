#include <stdio.h>
#include <string.h>
#include "strbuf.h"
#include "lib/contracts.h"

/*
void test()
{
  struct strbuf *sb = strbuf(2);
}
*/

void test()
{
  // tests for strbuf_new
  struct strbuf* sb = strbuf_new(2);
  printf("strbuf_new() passes tests\n");

  // tests for strbuf_add
  strbuf_add(sb, "H", 1);
  ASSERT(sb->len == 1);
  ASSERT(sb->limit == 2);
  strbuf_add(sb, "ello", 4);
  ASSERT(sb->len == 5);
  strbuf_addstr(sb, ",world!");
  ASSERT(sb->len == 12);
  printf("strbuf_add() and strbuf_addstr() passes tests\n");

  char *s = strbuf_str(sb);
  ASSERT(strcmp(s, "Hello,world!") == 0);
  free(s);
  printf("strbuf_str() passes tests\n");

  char c = strbuf_pop(sb);
  ASSERT(c = '!');
  s = strbuf_str(sb);
  ASSERT(strcmp(s, "Hello,world") == 0);
  free(s);
  printf("strbuf_pop() passes tests\n");

  strbuf_delete(sb, 5);
  s = strbuf_str(sb);
  ASSERT(strcmp(s, "Helloworld") == 0);
  free(s);
  printf("strbuf_delete() passes tests\n");

  strbuf_push(sb, c);
  s = strbuf_str(sb);
  ASSERT(strcmp(s, "Helloworld!") == 0);
  free(s);
  printf("strbuf_push() passes tests\n");

  free(strbuf_dealloc(sb));
  return;
}


int main()
{
  test();
  return 0;
}
