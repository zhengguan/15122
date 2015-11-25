
/* 
 * Hash tables interface
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#include "bitarray.h"
#include "hset.h"

#ifndef _BITARRAY_HASHTABLE_H_
#define _BITARRAY_HASHTABLE_H_

struct board_data {
  uint8_t last_move;
  bitarray board;
};

/* IMPORTANT: Please respect the hash set interface in hset.h
 * when writing your implementation of these functions!
 */

/* Initializes a new hash table with the given capacity
 */
hset ht_new(size_t capacity);

/* ht_insert(H,e) has no return value, because it should have as
 * a precondition that no struct currently in the hashtable contains
 * the same board as DAT->board
 */
void ht_insert(hset H, struct board_data *DAT);

/* ht_lookup(H,B) returns 
 * NULL if no struct containing the board B exists in H
 * A struct containing the board B if one exists in H
 */
struct board_data *ht_lookup(hset H, bitarray B);

/* Frees the hash table and all of its data
 */
void ht_free(hset H);

#endif
