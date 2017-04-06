#pragma once 

#include "utils.h"
#include "message.h"
#include "binary_tree.h"

struct heap_t {
    int size;
    int count;
    struct node_t **alphabet;
};

struct node_t *heap_min(struct heap_t *);
int heap_delete(struct heap_t *);
int heap_print(struct heap_t *);
int heap_push(struct heap_t *, struct node_t *);
struct heap_t *heap_init(unsigned int);
struct node_t *tree_from_heap(struct heap_t *);