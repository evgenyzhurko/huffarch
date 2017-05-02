/**
    @file code_table.c

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#include "code_table.h"

/**
 @brief Concoding table from binary tree.

 This function generate coding table from binary tree.
 Also, this function generate code for each character,
 based on depth search.

 @param[in] node Root of the binary tree.
 @return Array of cells - coding table.
*/
cell_t *table_from_tree(node_t *node)
{
    uint_fast16_t i, j;
    uint_fast64_t k;
    node_t *leaf;
    node_t *tmp;
    cell_t *table = malloc(sizeof(*table) * N_ALPHA);
    IS_NULL(table);

    for (i = 0; i < N_ALPHA; i++) {
        leaf = find_node(node, i);
        if (leaf != NULL) {
            int depth = 0;
            tmp = leaf;

            if (leaf == node) {
                depth++;
            }
            else {
                while (tmp->parent != NULL) {
                    tmp = tmp->parent;
                    depth++;
                }
            }

            tmp = leaf;
            table[i].c = leaf->element->c;
            table[i].frequency = leaf->element->frequency;
            table[i].length = depth;

            if (leaf != node) {
                for (j = depth, k = 1; j >= 1; j--, k <<= 1) {
                    table[i].code |= (tmp->parent->left == tmp) ? 0 : k;
                    tmp = tmp->parent;
                }
            }
            else {
                table[i].code = 1;
            }
            continue;
        }
        table[i].length = 0;
        table[i].code = 0;
    }

    return table;
}

/**
 @brief Delete table and free memory for it.

 This function delete all cells in table with all content.

 @param[in] node Root of the binary tree.
 @return Execution status.
*/
int table_delete(cell_t *table)
{
    FREE_PTR(table);
    return 0;
}

/**
 @brief Print table.

 This fucntion print all cells in table.

 @param[in] table Coding table.
 @return Execution status.
*/
int table_print(cell_t *table)
{
    uint_fast32_t i;

    for (i = 0; i < N_ALPHA;  i++) {
        if (table[i].length != 0) {
            printf("%d - %zu - %u - ", table[i].c, table[i].frequency, table[i].length);
            printf("%zu\n", table[i].code);
        }
    }
    return 0;
}

/**
 @brief Length of table.

 This fucntion define size of encoded file.
 Results gets by sum of code for all character in table.

 @param[in] table Coding table.
 @return length of table.
*/
uint_fast64_t table_result(cell_t *table)
{
    uint_fast32_t i;
    uint_fast64_t result = 0;

    for (i = 0; i < N_ALPHA;  i++) {
        if (table[i].length != 0) {
            result += table[i].length * table[i].frequency;
        }
    }

    return result;
}