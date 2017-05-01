/**
    @file utils.c

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#include "utils.h"

/**
 @brief Find size of input file

 @param[in] file File
 @return Size of file
*/
int file_size(FILE *file)
{
    int size;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    rewind(file);

    return size;
}

/**
 @brief Open file

 @param[in] file File
 @return File descriptor
*/
FILE* file_open(char *name, char *option)
{
    FILE *file = fopen(name, option);

    if (file == NULL) {
        PRINT_FILE(name);
        return NULL;
    }

    return file;
}

/**
 @brief Close file

 @param[in] file File
 @return Execution status
*/
int file_close(FILE *file)
{
    fclose(file);
    file = NULL;
    return 0;
}