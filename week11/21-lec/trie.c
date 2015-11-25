/*
 * Ternary search tries
 *
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning, Don Huang, Rob Simmons */

#include <assert.h>
#include <string.h>
#include <limits.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "trie.h"
#include "queue.h"
#include "strbuf.h".

// tnode now defined in tries2.h
typedef struct trie_node tnode;
struct trie_node {
  char c;            /* discriminating character */
  bool is_end;       /* is this the end of a trie? */
  tnode *left;       /* left child in bst */
  tnode *middle;     /* subtrie following c */
  tnode *right;      /* right child in bst */
};

struct trie_header {
  tnode *root;
};

/* checking invariants */
bool is_tnode(tnode *T, int lower, int upper);
bool is_tnode_root(tnode *T);

/* bounds are used as in is_bst */
bool is_tnode(tnode *T, int lower, int upper) {
  if (T == NULL) return true;
  if (T->middle == NULL && !T->is_end) return false;
  return (lower < (int)T->c && (int)T->c < upper)
    && is_tnode(T->left, lower, T->c)
    && is_tnode_root(T->middle)
    && is_tnode(T->right, T->c, upper);
}

bool is_tnode_root(tnode *T) {
  return is_tnode(T, 0, ((int)CHAR_MAX)+1);
}

bool is_trie(struct trie_header *TR) {
  return TR != NULL
    && is_tnode_root(TR->root);
}

trie trie_new() {
  trie TR = xmalloc(sizeof(struct trie_header));
  TR->root = NULL;
  ENSURES(is_trie(TR));
  return TR;
}

// GIVEN: a tnode T and a non-empty string s[i,)
// RETURNS: if s[i,) is a prefix of T, return the node that corresponding
// to the last char of s, otherwise return NULL
tnode *tnode_lookup(tnode *T, char *s, size_t i) {
  REQUIRES(is_tnode_root(T));
  REQUIRES(s != NULL);
  REQUIRES(i < strlen(s));

  if (T == NULL) return NULL;
  if (s[i] < T->c) return tnode_lookup(T->left, s, i);
  if (s[i] > T->c) return tnode_lookup(T->right, s, i);
  if (s[i+1] == '\0') return T;

  return tnode_lookup(T->middle, s, i+1);
}

// RETURNS: true iff the given trie TR contains a member that equal to s
bool trie_member(trie TR, char *s) {
  REQUIRES(is_trie(TR));
  REQUIRES(s != NULL && strlen(s) > 0);

  tnode *T = tnode_lookup(TR->root, s, 0);

  return T != NULL && T->is_end;
}

bool trie_prefix(trie TR, char *s) {
  REQUIRES(is_trie(TR));
  REQUIRES(s != NULL && strlen(s) > 0);

  tnode *T = tnode_lookup(TR->root, s, 0);

  return T != NULL && T->middle != NULL;
}

// EFFECT: insert s[t,) into T
// RETURNS: T after inserted s[t,)
tnode *tnode_insert(tnode *T, char *s, size_t i)
{
  REQUIRES(is_tnode_root(T));
  REQUIRES(s != NULL);
  REQUIRES(i < strlen(s));

  if (T == NULL)
  {
    T = xmalloc(sizeof(struct trie_node));
    T->c = s[i];
    T->is_end = false;
    T->left = NULL;
    T->right = NULL;
    T->middle = NULL;
  }

  if (s[i] < T->c) T->left = tnode_insert(T->left, s, i);
  else if (s[i] > T->c) T->right = tnode_insert(T->right, s, i);
  else if (s[i+1] == '\0') T->is_end = true;
  else T->middle = tnode_insert(T->middle, s, i+1);

  ENSURES(is_tnode_root(T));
  return T;
}

void trie_insert(trie TR, char *s) {
  REQUIRES(is_trie(TR));
  REQUIRES(s != NULL);
  TR->root = tnode_insert(TR->root, s, 0);
}

void tnode_free(tnode *T) {
  REQUIRES(is_tnode_root(T));
  if (T == NULL) return;
  tnode_free(T->left);
  tnode_free(T->middle);
  tnode_free(T->right);
  free(T);
}

void trie_free(trie TR) {
  REQUIRES(is_trie(TR));
  tnode_free(TR->root);
  free(TR);
}

/******************************************************************************/
// Ex 3 of lec 21

// WHERE: 0 <= start && start < strlen(s);
// EFFECT: for each member m of tn that matches s[start,)
// add the concatenation of sb and m to q
// DETAILS: the sb should have the same string as before afetr
// the function returns
void tnode_lookup_generalized(tnode *tn, char *s, size_t start,
                              struct strbuf *sb, Queue q) {
  REQUIRES(is_tnode(tn));
  REQUIRES(s != NULL && 0 <= start && start < strlen(s));
  REQUIRES(is_strbuf(sb));
  REQUIRES(is_Queue(q));

  if (s[start] == '*') {
    if (tn == NULL) return;
    tnode_lookup_generalized(tn->left, s, start, sb, q);
    tnode_lookup_generalized(tn->right, s, start, sb, q);

    if (s[start + 1] == '\0' && tn->is_end) {
      strbuf_push(sb, s[start]);
      Queue_insert(q, strbuf_str(sb));
      strbuf_pop(sb);
      return;
    } else if (s[start + 1] == '\0') {
      tnode_lookup_generalized(tn->middle, s, start, sb, q);
    } else {
      ASSERT(s[start + 1] != '\n');
      strbuf_push(sb, s[start]);
      tnode_lookup_generalized(tn->middle, s, start, sb, q);
      tnode_lookup_generalized(tn->middle, s, start + 1, sb, q);
      strbuf_pop(sb);
    }
  } else {
    if (tn == NULL) return;
    if (s[i] < tn->c) {
      tnode_lookup_generalized(T->left, s, i, sb, q);
      return;
    } else if (s[i] > tn->c) {
      tnode_lookup_generalize(T->right, s, i, sb, q);
      return;
    } else if (s[i+1] == '\0') {
      strbuf_push(sb, s[i]);
      Queue_insert(q, sb);
      strbuf_pop(sb);
      return;
    }

    tnode_lookup(T->middle, s, i+1);
  }

  ENSURES(is_Queue(q));
}

// DETAILS: s might contains '*' which representa arbitrary number of arbitrary
// character
// EFFECT: add all members in the given T that match the given string
// s to q
void trie_member_generalized(trie T, char *s, Queue q) {
  REQUIRES(is_trie(T));
  REQUIRES(s != NULL);
  REQUIRES(is_Queue(q));

  struct strbuf *sb = strbuf_new(8);
  tnode_lookup_generalized(T->root, s, 0, strlen(s), sb, q);
  free(strbuf_dealloc(sb));

  ENSURES(is_Queue(q));
  return;

}
