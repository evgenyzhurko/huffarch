#pragma once

#include "utils.h"
#include "binary_tree.h"

struct cell_t {
    unsigned char c;
    unsigned char *code;
    unsigned int length;
    unsigned int frequency;
};

struct cell_t *table_from_tree(struct node_t *);
int table_delete(struct cell_t *);
int table_print(struct cell_t *);
unsigned long int table_result(struct cell_t *);