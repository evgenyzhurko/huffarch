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
struct cell_t {
    /*@{*/
    uint_fast8_t c; /**< character */
    uint_fast8_t length; /**< length of huffman code */
    uint_fast64_t code; /**< code, sequence of 0 and 1 */
    uint_fast64_t frequency; /**<  frequency of character*/
    /*@}*/
};

struct cell_t *table_from_tree(struct node_t *);
int table_delete(struct cell_t *);
int table_print(struct cell_t *);
uint_fast64_t table_result(struct cell_t *);