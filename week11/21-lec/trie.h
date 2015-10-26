/* 
 * Ternary search tries
 *
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning, Don Huang, Rob Simmons
 */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _TRIES_H_
#define _TRIES_H_

typedef void *elem;
typedef struct trie_header *trie;

trie trie_new();
void trie_free(trie TR);
void trie_insert(trie TR, char *s); /* strlen(s) > 0 */
bool trie_member(trie TR, char *s); /* strlen(s) > 0 */
bool trie_prefix(trie TR, char *s); /* strlen(s) > 0, proper prefix */

#endif
