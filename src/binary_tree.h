/**
    @file binary_tree.h

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma once

#include "utils.h"

/**
 * This struct defines data structure to contain character 
 * with frequency as one part.
 */
struct pair_t {
    /*@{*/
    unsigned char c; /**< the character */
    unsigned int frequency; /** < frequence for this character*/
    /*@}*/
};

/**
 * Data structure that define node of binary tree.
 */
struct node_t {
    /*@{*/
    char is_leaf; /**< flag to know is leaf or not*/
    /*@}*/
    /*@{*/
    struct pair_t *element; /**< character with frequence*/
    struct node_t *parent; /**< parent node*/
    struct node_t *left; /**< left node*/
    struct node_t *right; /**< right node*/
    /*@{*/
};

struct node_t *find_node(struct node_t *, unsigned char);
struct node_t *create_node(unsigned char, unsigned int, unsigned int);
int tree_print(struct node_t *);
int tree_delete(struct node_t *);
struct node_t *merge_tree(struct node_t *, struct node_t *);