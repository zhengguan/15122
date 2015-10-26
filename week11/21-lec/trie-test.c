/*
 * Testing tries
 *
 * 15-122 Principles of Imperative Computation, Fall 2012
 * Frank Pfenning, Tom Cortina, Rob Simmons
 */

#include <stdio.h>
#include <string.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"

#include "trie.h"

int main() {
  int limit = 1<<10; /* 10 = 1K, 20 = 1M */
  char** A = xcalloc(limit, sizeof(char *));

  // Generate some fake string data using numbers
  for (int i = 0; i < limit; i++) {
    char* s = xmalloc(15 * sizeof(char));
    sprintf(s, "%d", 7*i%limit);

    // convert to word characters: "30022" --> "daacc"
    for (int j = 0; s[j] != '\0' && j < 15 ; j++)
      s[j] += ('a' - '0');	
     
    A[i] = s;
  }

  // Insert string data into the tree
  trie TR = trie_new();
  for (int i = 0; i < limit; i++) {
    assert(!trie_member(TR, A[i])); // String not there yet
    trie_insert(TR, A[i]);          // ... but once we add it 
    assert(trie_member(TR, A[i]));  // ... it had better be there
  }

  printf("Stored %d words.\n", limit);
  for (int i = 0; i < limit; i++) {
    assert(trie_member(TR, A[i]));  /* string found after all inserts */
    free (A[i]);
  }
  free(A);
  A = NULL;

  printf("First set of tests passed!\n");
  assert(!trie_member(TR, "foo"));
  assert(!trie_member(TR, "srcambled"));
  assert(!trie_member(TR, "x"));
  assert(!trie_member(TR, "aq"));
  trie_free(TR);
  printf("Second set of tests passed!\n");

  TR = trie_new();
  trie_insert(TR, "bed");
  trie_insert(TR, "bad");
  trie_insert(TR, "bay");
  trie_insert(TR, "bays");
  
  assert( trie_prefix(TR, "b"));
  assert(!trie_member(TR, "b"));
  assert( trie_prefix(TR, "be"));
  assert(!trie_member(TR, "be"));
  assert(!trie_prefix(TR, "bed"));
  assert( trie_member(TR, "bed"));

  assert( trie_prefix(TR, "ba"));
  assert(!trie_member(TR, "ba"));
  assert(!trie_prefix(TR, "bad"));
  assert( trie_member(TR, "bad"));

  assert( trie_prefix(TR, "bay"));
  assert( trie_member(TR, "bay"));

  assert(!trie_prefix(TR, "bays"));
  assert( trie_member(TR, "bays"));

  assert(!trie_prefix(TR, "bat"));
  assert(!trie_member(TR, "bat"));

  trie_free(TR);
  printf("Third set of tests passed!\n");

  return 0;
}
