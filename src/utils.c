#include "utils.h"

int file_size(FILE *file)
{
    int size;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    rewind(file);

    return size;
}

FILE* file_open(char *name, char *option)
{
    FILE *file = fopen(name, option);

    if (file == NULL) {
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