/**
    @file code_table.h

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma once

#include <stdint.h>

#include "utils.h"
#include "binary_tree.h"

/**
 * This data structure defines cell of coding table.
 * Each cell contain symbols with huffman code.
 */
typedef struct {
    /*@{*/
    uint_fast8_t c; /**< character */
    uint_fast8_t length; /**< length of huffman code */
    uint_fast64_t code; /**< code, sequence of 0 and 1 */
    uint_fast64_t frequency; /**<  frequency of character*/
    /*@}*/
} cell_t;

cell_t *table_from_tree(node_t *);
int table_delete(cell_t *);
int table_print(cell_t *);
uint_fast64_t table_result(cell_t *);