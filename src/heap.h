/**
    @file heap.h

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma once 

#include "utils.h"
#include "message.h"
#include "binary_tree.h"

/**
 * This struct defines priority heap that contain
 */
struct heap_t {
    /*@{*/
    int size; /**< max size f heap */
    int count; /**< current size of heap */
    /*@}*/
    /*@{*/
    struct node_t **alphabet; /**< element of heap */
    /*@{*/
};

struct node_t *heap_min(struct heap_t *);
int heap_delete(struct heap_t *);
int heap_print(struct heap_t *);
int heap_push(struct heap_t *, struct node_t *);
struct heap_t *heap_init(unsigned int);
struct node_t *tree_from_heap(struct heap_t *);