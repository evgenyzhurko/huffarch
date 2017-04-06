 #pragma once

#include "utils.h"

struct pair_t {
    unsigned char c;
    unsigned int frequency;
};

struct node_t {
    char is_leaf;
    struct pair_t *element;
    struct node_t *parent;
    struct node_t *left;
    struct node_t *right;
};

struct node_t *find_node(struct node_t *, unsigned char);
struct node_t *create_node(unsigned char, unsigned int, unsigned int);
int tree_print(struct node_t *);
int tree_delete(struct node_t *);
struct node_t *merge_tree(struct node_t *, struct node_t *);