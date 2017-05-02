/**
    @file binary_tree.h

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma once

#include "utils.h"

typedef struct node node_t;

/**
 * This struct defines data structure to contain character 
 * with frequency as one part.
 */
typedef struct {
    /*@{*/
    unsigned char c; /**< the character */
    unsigned int frequency; /** < frequence for this character*/
    /*@}*/
} pair_t;

/**
 * Data structure that define node of binary tree.
 */
struct node {
    /*@{*/
    char is_leaf; /**< flag to know is leaf or not*/
    /*@}*/
    /*@{*/
    pair_t *element; /**< character with frequence*/
    node_t *parent; /**< parent node*/
    node_t *left; /**< left node*/
    node_t *right; /**< right node*/
    /*@{*/
};

node_t *find_node(node_t *, unsigned char);
node_t *create_node(unsigned char, unsigned int, unsigned int);
int tree_print(node_t *);
int tree_delete(node_t *);
node_t *merge_tree(node_t *, node_t *);