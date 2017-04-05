#include "utils.h"

int file_size(FILE *desc)
{
    int size;

    fseek(desc, 0L, SEEK_END);
    size = ftell(desc);
    rewind(desc);

    return size;
}

FILE* file_open(char *name, char *option)
{
    FILE *file = fopen(name, option);

    if (file == NULL)
    {
        PRINT_FILE(name);
        return NULL;
    }

    return file;
}

int file_close(FILE *file)
{
    fclose(file);
    file = NULL;
    return 0;
}