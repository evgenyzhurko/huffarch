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
 * This defines priority heap that contain
 */
typedef struct {
    /*@{*/
    int size; /**< max size f heap */
    int count; /**< current size of heap */
    /*@}*/
    /*@{*/
    node_t **alphabet; /**< element of heap */
    /*@{*/
} heap_t;

node_t *heap_min(heap_t *);
int heap_delete(heap_t *);
int heap_print(heap_t *);
int heap_push(heap_t *, node_t *);
heap_t *heap_init(unsigned int);
node_t *tree_from_heap(heap_t *);