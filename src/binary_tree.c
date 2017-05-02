/**
    @file binary_tree.c

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#include "binary_tree.h"

/**
 @brief Print binary tree

 This function print binary tree.
 Root node will be printed first.
 Then will be printed left subtree with all elements.
 And after left subtree will be printed right subtree
 with all elements.

 @param[in] node Root of the binary tree
 @return Execution status
*/
int tree_print(node_t *node)
{
    if (node == NULL) {
        return 1;
    }

    if (!node->is_leaf) {
        printf("%d - %d\n", node->is_leaf, node->element->frequency);
    }
    else {
        printf("%d - %c - %d\n", node->is_leaf, node->element->c,
            node->element->frequency);
    }

    tree_print(node->left);
    tree_print(node->right);
    return 0;
}

/**
 @brief Delete binary tree

 This function delete binary tree with all elements.

 @param[in] node Root of the binary tree
 @return Execution status
*/
int tree_delete(node_t *node)
{
    if (node == NULL) {
        return 1;
    }

    tree_delete(node->left);
    tree_delete(node->right);
    FREE_PTR(node->element);
    FREE_PTR(node);
    return 0;
}

/**
 @brief Create new node with given parameters

 This function connew node for tree with given parameters.

 @param[in] c Define character for this node
 @param[in] frequency Define frequency for character
 @param[in] is_leaf Define is leaf or intermediate node
 @return New node
*/
node_t *create_node(unsigned char c, unsigned int frequency, unsigned int is_leaf)
{
    pair_t *pair_new;
    node_t *node_new;

    pair_new = malloc(sizeof(*pair_new));
    node_new = malloc(sizeof(*node_new));

    IS_NULL(pair_new);
    IS_NULL(node_new);

    pair_new->c = c;
    pair_new->frequency = frequency;
    node_new->element = pair_new;
    node_new->is_leaf = is_leaf;
    node_new->parent = NULL;
    node_new->left = NULL;
    node_new->right = NULL;

    return node_new;
}

/**
 @brief Merge two tree into one tree 

 Create new tree from two tree.
 One of the tree will be left subtree, the other will be right subtree.

 @param[in] left Left tree
 @param[in] right Right tree
 @return New tree
*/
node_t *merge_tree(node_t *left, node_t *right)
{
    node_t *node_new = NULL;

    node_new = create_node(0, 0, 0);

    left->parent = node_new;
    right->parent = node_new;
    node_new->left = left;
    node_new->right = right;
    node_new->element->frequency = left->element->frequency +\
        right->element->frequency;
    return node_new;
}

/**
 @brief Find node by character

 This function find charater in tree.
 If character isn't find function return NULL.

 @param[in] node Root node
 @param[in] c Character to find in tree
 @return node Lead that contain this character or NULL(if not find)
*/
node_t *find_node(node_t *node, unsigned char c)
{
    if (node == NULL) {
        return NULL;
    }

    if (node->is_leaf) {
        if (node->element->c == c) {
            return node;
        }
        return NULL;
    }
    else {
        node_t *left = find_node(node->left, c);
        node_t *right = find_node(node->right, c);

        if (left != NULL) {
            return left;
        }
        else if (right != NULL) {
            return right;
        }
        return NULL;
    }
}