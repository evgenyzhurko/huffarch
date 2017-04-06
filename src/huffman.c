#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

#include "huffman.h"

int extract(char *ifile_name, char *ofile_name)
{
    unsigned int i, size;
    unsigned char elements;
    struct heap_t *heap = NULL;
    struct node_t *tree = NULL;
    FILE* ifile = file_open(ifile_name, "rb");
    FILE* ofile = file_open(ofile_name, "wb");

    if (ifile == NULL || ofile == NULL) {
        return 1;
    }    

    size = file_size(ifile);

    if (size == 0) {
        PRINT_ERROR(FILE_ZERO_SIZE);
        file_close(ifile);
        file_close(ofile);
        return 1;
    }

    fread(&elements, sizeof(char), 1, ifile);

    heap = heap_init(N_ALPHA);

    for (i = 0; i < elements; i++) {
        unsigned char c;
        unsigned int frequency;

        fread(&c, 1, sizeof(c), ifile);
        fread(&frequency, 1, sizeof(frequency), ifile);

        struct node_t *node_new = create_node(c, frequency, 1);

        heap_push(heap, node_new);
    }

    tree = tree_from_heap(heap);

    decode(tree, ifile, ofile);

    tree_delete(tree);
    heap_delete(heap);
    file_close(ifile);
    file_close(ofile);
    return 0;
}

int compress(char *ifile_name, char *ofile_name)
{
    unsigned char elements;
    unsigned int i, n, size;
    unsigned char buffer[N];
    unsigned int alphabet[N_ALPHA] = {0};
    struct heap_t *heap = NULL;
    struct node_t *tree = NULL;
    struct cell_t *table = NULL;
    FILE* ifile = file_open(ifile_name, "rb");
    FILE* ofile = file_open(ofile_name, "wb");

    if (ifile == NULL || ofile == NULL)
    {
        return 1;
    }

    size = file_size(ifile);

    if (size == 0) {
        PRINT_ERROR(FILE_ZERO_SIZE);
        return 1;
    }

    while ((n = fread(buffer, 1, N, ifile))) {
        for (i = 0; i < n; i++) {
            alphabet[(unsigned int)buffer[i]]++;
        }
    }

    elements = 0;
    for (i = 0; i < N_ALPHA; i++) {
        alphabet[i] != 0 ? elements++ : 0;
    }

    heap = heap_init(N_ALPHA);
    fwrite(&elements, sizeof(unsigned char), 1, ofile);

    for (i = 0; i < N_ALPHA; i++) {
        if (alphabet[i] != 0) {
            struct node_t *node_new = create_node(i, alphabet[i], 1);
            heap_push(heap, node_new);

            fwrite(&i, sizeof(unsigned char), 1, ofile);
            fwrite(&alphabet[i], sizeof(unsigned int), 1, ofile);
        }
    }

    tree = tree_from_heap(heap);

    table = table_from_tree(tree);

    encode(table, ifile, ofile);

    table_delete(table);
    heap_delete(heap);
    tree_delete(tree);
    file_close(ifile);
    file_close(ofile);
    return 0;
}

int encode(struct cell_t *table, FILE *ifile, FILE *ofile)
{
    unsigned int ii, io, ji, jo, k, n;
    unsigned char ibuffer[N];
    unsigned char obuffer[N];

    rewind(ifile);

    io = 0;
    jo = 0;

    while ((n = fread(ibuffer, 1, N, ifile))) {
        for (ii = 0; ii < n; ii++) {
            k = ibuffer[ii];
            for (ji = 0; ji < table[k].length; ji++) {
                obuffer[io] = (obuffer[io] << 1) | table[k].code[ji];
                jo++;
                if (jo == 8) {
                    io++;
                    jo = 0;
                    if (io == N) {
                        fwrite(obuffer, sizeof(unsigned char), N, ofile);
                        io = 0;
                    }
                }
            }
        }
    }

    if (io != 0) {
        if (jo > 0) {
            obuffer[io] = obuffer[io] << (8 - jo);
            io++;
        }
        fwrite(obuffer, sizeof(unsigned char), io, ofile);
    }

    return 0;
}

int decode(struct node_t *node, FILE *ifile, FILE *ofile)
{
    unsigned int ii, io, ji, n;
    unsigned long int elements;
    unsigned char ibuffer[N];
    unsigned char obuffer[N];
    struct node_t *leaf = node;

    io = 0;
    elements = 0;

    while ((n = fread(ibuffer, 1, N, ifile))) {
        for (ii = 0; ii < n; ii++) {
            for (ji = 8; ji >= 1; ji--) {
                unsigned char c = ibuffer[ii];
                if ((c >> (ji - 1)) & 1) {
                    leaf = leaf->right;
                }
                else {
                    leaf = leaf->left;
                }
                if (leaf->is_leaf) {
                    if (elements == node->element->frequency) {
                        leaf = node;
                        break;
                    }
                    obuffer[io] = leaf->element->c;
                    io++;
                    elements++;
                    leaf = node;
                    if (io == N) {
                        fwrite(obuffer, sizeof(char), N, ofile);
                        io = 0;
                    }
                }
            }
        }
        if (n < N) {
            break;
        }
    }

    if (io != 0) {
        fwrite(obuffer, sizeof(char), io, ofile);
    }

    return 0;
}