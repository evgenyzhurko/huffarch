#include "binary_tree.h"

int tree_print(struct node_t *node)
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

int tree_delete(struct node_t *node)
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

struct node_t *create_node(unsigned char c, unsigned int frequency, unsigned int is_leaf)
{
    struct pair_t *pair_new;
    struct node_t *node_new;

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

struct node_t *merge_tree(struct node_t *left, struct node_t *right)
{
    struct node_t *node_new = NULL;

    node_new = create_node(0, 0, 0);

    left->parent = node_new;
    right->parent = node_new;
    node_new->left = left;
    node_new->right = right;
    node_new->element->frequency = left->element->frequency +\
        right->element->frequency;
    return node_new;
}


struct node_t *find_node(struct node_t *node, unsigned char c)
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
        struct node_t *left = find_node(node->left, c);
        struct node_t *right = find_node(node->right, c);

        if (left != NULL) {
            return left;
        }
        else if (right != NULL) {
            return right;
        }
        return NULL;
    }
}