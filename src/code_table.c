#include "code_table.h"

struct cell_t *table_from_tree(struct node_t *node)
{
    uint_fast16_t i, j;
    uint_fast64_t k;
    struct node_t *leaf;
    struct node_t *tmp;
    struct cell_t *table = malloc(sizeof(*table) * N_ALPHA);
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

int table_delete(struct cell_t *table)
{
    FREE_PTR(table);
    return 0;
}

int table_print(struct cell_t *table)
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

uint_fast64_t table_result(struct cell_t *table)
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