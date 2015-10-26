#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "strbuf.h"


struct strbuf* strbuf_new(size_t init_limit);
char* strbuf_str(struct strbuf *sb);
void strbuf_add(struct strbuf *sb, char *str, size_t len);
void strbuf_addstr(struct strbuf *sb, char *str);


/*** Implementation ***/

// GIVEN: an array and an int
// REUTNRS: true iff the given int is the given array's length
/*
bool is_specified_length(char* buf, int len) {
  return strlen(buf) == (size_t)len;
}
*/

bool is_strbuf(struct strbuf* sb) {
  return sb != NULL
    && sb->len < sb->limit // one byte for '\0'
    && strlen(sb->buf) == sb->len;
}

struct strbuf* strbuf_new(size_t initial_limit)
{
  REQUIRES(initial_limit > 0);

  struct strbuf *sb = xcalloc(1, sizeof(struct strbuf));
  sb->limit = initial_limit;
  sb->buf = xcalloc(initial_limit, sizeof(char));
  sb->len = 0;
  sb->buf[0] = '\0';

  ENSURES(is_strbuf(sb));
  return sb;
}

char *strbuf_dealloc(struct strbuf *sb)
{
  REQUIRES(is_strbuf(sb));

  char *s = sb->buf;
  free(sb);
  return s;
}

// RETURNS: a copy of string in the given string buffer
char* strbuf_str(struct strbuf* str)
{
  REQUIRES(is_strbuf(str));

  char* arr = xcalloc(str->len + 1, sizeof(char));
  strncpy(arr, str->buf, str->len + 1);

  ENSURES(strlen(arr) == str->len);
  return arr;
}

// EFFECT: concate the first str_len characters in str
// to the string in sb,
void strbuf_add(struct strbuf* sb, char* str, size_t str_len)
{
  REQUIRES(is_strbuf(sb));

  if (sb->len + str_len >= sb->limit) {
    size_t new_limit = (sb->len + str_len) * 2;
    char* buf = xcalloc(new_limit, sizeof(char));
    strncpy(buf, sb->buf, sb->len);
    free(sb->buf);
    sb->buf = buf;
    sb->limit = new_limit;
  }
  ASSERT(sb->len + str_len < sb->limit);
  strncpy(&(sb->buf[sb->len]), str, str_len);
  sb->len = sb->len + str_len;
  sb->buf[sb->len] = '\0';

  ENSURES(is_strbuf(sb));
  return;
}

void strbuf_addstr(struct strbuf *sb, char *str)
{
  REQUIRES(is_strbuf(sb));

  strbuf_add(sb, str, strlen(str));

  ENSURES(is_strbuf(sb));
}
