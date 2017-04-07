#include "code_table.h"

struct cell_t *table_from_tree(struct node_t *node)
{
    int i, j;
    struct node_t *leaf;
    struct node_t *tmp;
    struct cell_t *table = malloc(sizeof(*table) * N_ALPHA);
    IS_NULL(table);

    for (i = 0; i < N_ALPHA; i++) {
        leaf = find_node(node, i);
        if (leaf != NULL) {
            int depth = 0;
            tmp = leaf;

            while (tmp->parent != NULL) {
                tmp = tmp->parent;
                depth++;
            }

            tmp = leaf;
            table[i].c = leaf->element->c;
            table[i].frequency = leaf->element->frequency;
            table[i].length = depth;

            table[i].code = malloc(sizeof(*(table[i].code)) * depth);
            IS_NULL(table[i].code);

            for (j = depth - 1; j >= 0; j--) {
                table[i].code[j] = (tmp->parent->left == tmp) ? 0 : 1;
                tmp = tmp->parent;
            }
            continue;
        }
        table[i].length = 0;
        table[i].code = NULL;
    }

    return table;
}

int table_delete(struct cell_t *table)
{
    int i;

    for (i = 0; i < N_ALPHA;  i++) {
        FREE_PTR(table[i].code);
    }

    FREE_PTR(table);
    return 0;
}

int table_print(struct cell_t *table)
{
    int i, j;

    for (i = 0; i < N_ALPHA;  i++) {
        if (table[i].length != 0) {
            printf("%d - %d - %d - ", table[i].c, table[i].frequency, table[i].length);
            for (j = 0; j < table[i].length; j++) {
                printf("%d", table[i].code[j]);
            }
            printf("\n");
        }
    }
    return 0;
}

unsigned long int table_result(struct cell_t *table)
{
    int i;
    unsigned long int result = 0;

    for (i = 0; i < N_ALPHA;  i++) {
        if (table[i].length != 0) {
            result += table[i].length * table[i].frequency;
        }
    }

    return result;
}