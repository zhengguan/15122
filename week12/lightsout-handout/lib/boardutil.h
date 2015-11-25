/* 
 * Board utilities
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdint.h>
#include "bitarray.h"

#ifndef _BOARDUTIL_H_
#define _BOARDUTIL_H_

/* Check whether a width and height ar valid boards, 
 * representable as bitarrays */
bool is_valid_boardsize(uint8_t width, uint8_t height);

/* Check whether row and column are valid boards for the given width
 * and height
 * 
 * Requires: is_valid_boardsize(width, height) */
bool is_valid_pos(int row, int col, uint8_t width, uint8_t height);

/* Get the index for a position (standard row-major ordering used in
 * the image and peg solitaire assignments)
 *
 * Requires: is_valid_boardsize(width, height)
 * Requires: is_valid_pos(row, col, width, height) */
uint8_t get_index(int row, int col, uint8_t width, uint8_t height);

/* Tries to read a lightboard from the file 'path'
 * Failure: returns false
 * Success: writes the array of bits into 'arr_out'
 *          writes the width into 'width_out'
 *          writes the height into 'height_out'
 * 
 * Requires: All non-NULL pointers, path must be a string
 * Ensures: !\result || is_valid_boardsize(*width_out, *height_out) */
bool file_read(char *path, 
               bitarray *arr_out,
               uint8_t *width_out,
               uint8_t *height_out);

/* Prints a representation of the board to standard error
 *
 * Requires: is_valid_boardsize(width, height); */
void print_board(bitarray arr, uint8_t width, uint8_t height);

#endif
