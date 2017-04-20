#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

#include "huffman.h"

int extract(char *ifile_name, char *ofile_name)
{
    uint_fast32_t i, size;
    uint_fast8_t elements;
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

    fread(&elements, sizeof(elements), 1, ifile);

    heap = heap_init(N_ALPHA);

    size = ((elements == 0) ? 256 : elements);

    for (i = 0; i < size; i++) {
        uint_fast8_t c;
        uint_fast32_t frequency;

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
    uint_fast8_t elements;
    uint_fast32_t i, n, size;
    uint_fast8_t buffer[N];
    uint_fast32_t alphabet[N_ALPHA] = {0};
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
        PRINT_WARNING(FILE_ZERO_SIZE);
        return 1;
    }

    while ((n = fread(buffer, 1, N, ifile))) {
        for (i = 0; i < n; i++) {
            alphabet[(uint_fast8_t)buffer[i]]++;
        }
    }

    elements = 0;
    for (i = 0; i < N_ALPHA; i++) {
        alphabet[i] != 0 ? elements++ : 0;
    }

    heap = heap_init(N_ALPHA);
    fwrite(&elements, sizeof(elements), 1, ofile);

    for (i = 0; i < N_ALPHA; i++) {
        if (alphabet[i] != 0) {
            struct node_t *node_new = create_node(i, alphabet[i], 1);
            heap_push(heap, node_new);

            fwrite(&i, sizeof(uint8_t), 1, ofile);
            fwrite(&alphabet[i], sizeof(*alphabet), 1, ofile);
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
    uint_fast32_t ii, io, ji, k, n;
    uint_fast64_t length;
    uint8_t jo, left;
    uint_fast8_t ibuffer[N];
    uint_fast64_t obuffer[N];
    register uint_fast64_t curr_sym, curr_code;

    rewind(ifile);

    io = 0;
    jo = 64;
    curr_sym = 0;
 
    while ((n = fread(ibuffer, sizeof(*ibuffer), N, ifile))) {
        for (ii = 0; ii < n; ii++) {
            ji = 0;
            k = ibuffer[ii];
            length = table[k].length;
            curr_code = table[k].code;
            left = length;
            while (ji < length) {
                if (length > jo) {
                    curr_sym <<= jo;
                    left -= jo;
                    curr_sym |= (curr_code >> left);
                    obuffer[io] = curr_sym;
                    curr_sym = 0;
                    ji = jo;
                    jo = 64;
                    io++;
                }
                else {
                    curr_sym <<= left;
                    curr_sym |= ((curr_code << (63 - left)) >> (63 - left));
                    jo -= left;
                    ji = length;
                }
                if (io == N) {
                    fwrite(obuffer, sizeof(*obuffer), N, ofile);
                    io = 0;
                }
            }
        }
    }
 
    if (io != 0 || jo != 64) {
        if (jo != 64) {
            obuffer[io] = curr_sym << jo;
            io++;
        }
        fwrite(obuffer, sizeof(*obuffer), io, ofile);
    }

    return 0;
}

int decode(struct node_t *node, FILE *ifile, FILE *ofile)
{
    uint_fast64_t ii, io, ji, n, c;
    uint_fast64_t elements;
    uint_fast64_t ibuffer[N];
    uint_fast8_t obuffer[N];
    struct node_t *leaf = node;

    io = 0;
    elements = 0;

    while ((n = fread(ibuffer, sizeof(*ibuffer), N, ifile))) {
        for (ii = 0; ii < n; ii++) {
            c = ibuffer[ii];
            for (ji = 64; ji >= 1; ji--) {
                if (((c >> (ji - 1)) & 1) && !leaf->is_leaf) {
                    leaf = leaf->right;
                }
                else if (!leaf->is_leaf) {
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
                        fwrite(obuffer, sizeof(*obuffer), N, ofile);
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
        fwrite(obuffer, sizeof(*obuffer), io, ofile);
    }

    return 0;
}