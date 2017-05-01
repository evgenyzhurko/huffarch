/**
    @file heap.c

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#include "heap.h"

#include <stdio.h>

/**
 @brief Get minimal element from heap.

 This function return element.
 Minimal elements alsways contains in end of heap.

 @param[in] heap Heap
 @return Minimal element
*/
struct node_t *heap_min(struct heap_t *heap)
{
    IS_NULL(heap);
    heap->count--;
    return heap->alphabet[heap->count];
}

/**
 @brief Initialize heap

 This fucntion construct heap for given size.

 @param[in] size Size of desired heap.
 @return Heap
*/
struct heap_t *heap_init(unsigned int size)
{
    struct heap_t *heap;
    if (size == 0) {
        PRINT_ERROR(HEAP_ZERO_SIZE);
        return NULL;
    }

    heap = malloc(sizeof(*heap));
    IS_NULL(heap);

    heap->size = size;
    heap->count = 0;
    heap->alphabet = malloc(sizeof(*(heap->alphabet)) * 256);
    IS_NULL(heap->alphabet);

    return heap;
}

/**
 @brief Push one element into heap

 This function add given element into heap.
 It defines place for this element based on frequence of element.

 @param[in] heap Heap
 @param[in] node Element to insert
 @return Execution status
*/
int heap_push(struct heap_t *heap, struct node_t *node)
{
    int i;
    int inserted = 0;
    IS_NULL(heap);

    for (i = 0; i < heap->count; i++) {
        if (heap->alphabet[i]->element->frequency < node->element->frequency) {
            int j = heap->count;

            while (j != i) {
                heap->alphabet[j] = heap->alphabet[j - 1];
                j--;
            }

            inserted = 1;
            heap->alphabet[i] = node;
            break;
        }
    }

    if (!inserted) {
        heap->alphabet[heap->count] = node;
    }

    heap->count++;
    return 0;
}

/**
 @brief Delete heap

 This function delete heap with all content.

 @param[in] heap Heap
 @return Execution status
*/
int heap_delete(struct heap_t *heap)
{
    IS_NULL(heap);
    FREE_PTR(heap->alphabet);
    FREE_PTR(heap);
    return 0;
}

/**
 @brief Print heap

 This function print full content of heap o console line.

 @param[in] heap Heap
 @return Execution status
*/
int heap_print(struct heap_t *heap)
{
    int i;
    for (i = 0; i < heap->count; i++) {
        printf("%d - %c - %d\n", i, heap->alphabet[i]->element->c, 
            heap->alphabet[i]->element->frequency);
    }
    return 0;
}

/**
 @brief Construct tree from heap.

 This function create heap from tree.
 It's places all elements based on frequency.

 @param[in] heap Heap
 @return Root of binary tree
*/
struct node_t *tree_from_heap(struct heap_t *heap)
{
    struct node_t *left = NULL;
    struct node_t *right = NULL;
    struct node_t *parent = NULL;

    IS_NULL(heap);

    while (heap->count != 1) {
        left = heap_min(heap);
        right = heap_min(heap);
        parent = merge_tree(left, right);
        heap_push(heap, parent);
    }

    parent = heap_min(heap);
    return parent;
}
