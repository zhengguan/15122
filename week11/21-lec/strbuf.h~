/* 
 * String Buffer Library
 *
 * 15-122 Principles of Imperative Computation
 * This version exposes the externals, requires
 * discipline from client! */

#include <stdbool.h>
#include <stdlib.h>

#ifndef _STRBUF_H_
#define _STRBUF_H_

struct strbuf {
  size_t limit;   /* limit > 0, bytes allocated for buf */
  size_t len;     /* len < limit */
  char *buf;      /* buf != NULL, buf[len] == '\0', strlen(buf) == len */
};
bool is_strbuf(struct strbuf *sb);

struct strbuf *strbuf_new(size_t init_limit);
char *strbuf_dealloc(struct strbuf *sb);
char *strbuf_str(struct strbuf *sb);

void strbuf_add(struct strbuf *sb, char *str, size_t len);
void strbuf_addstr(struct strbuf *sb, char *str);

#endif
