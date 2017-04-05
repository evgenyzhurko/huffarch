#include "huffman.h"

int extract(char *ifile_name, char *ofile_name)
{
    FILE* ifile = file_open(ifile_name, "rb");
    FILE* ofile = file_open(ofile_name, "wb");

    if (ifile == NULL || ofile == NULL)
    {
        return 1;
    }

    printf("Extract: %s to %s\n", ifile_name, ofile_name);

    file_close(ifile);
    file_close(ofile);
    return 0;
}

int compress(char *ifile_name, char *ofile_name)
{
    int size;
    FILE* ifile = file_open(ifile_name, "rb");
    FILE* ofile = file_open(ofile_name, "wb");

    if (ifile == NULL || ofile == NULL)
    {
        return 1;
    }

    size = file_size(ifile);

    printf("Compress: %s to %s of %d bytes\n", ifile_name, ofile_name, size);

    file_close(ifile);
    file_close(ofile);
    return 0;
}