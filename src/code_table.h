#pragma once

#include <stdint.h>

#include "utils.h"
#include "binary_tree.h"

struct cell_t {
    uint_fast8_t c;
    uint_fast8_t length;
    uint_fast64_t code;
    uint_fast64_t frequency;
};

struct cell_t *table_from_tree(struct node_t *);
int table_delete(struct cell_t *);
int table_print(struct cell_t *);
uint_fast64_t table_result(struct cell_t *);