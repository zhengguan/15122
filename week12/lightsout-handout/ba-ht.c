#include <stdlib.h>
#include "lib/ba-ht.h"
#include "lib/xalloc.h"


hset ht_new(size_t capacity) {

}

// WHERE: H doesn't contains any struct that has the same
// board as DAT->board;
// EFFECT: insert DAT into H
void ht_insert(hset H, struct board_data *DAT) {

}

// RETURNS: NULL if no struct containing the board B exists in H,
// otherwise return the struct if exists;
struct board_dta *ht_lookup(hset H, bitarray B) {

}

void ht_free(hset H) {

}
