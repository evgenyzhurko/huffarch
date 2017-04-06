#pragma once

#include <stdio.h>

#define WRONG_INTERFACE "missing operand\
    \n\rTry 'huff -h' for more information\n"

#define WRONG_OPTION "unknown option"

#define CONTRADICTORY_OPTION "-c and -x is contradictory option,\n\
    \rPlease, use only one of them\n"

#define ZERO_SIZE "size can't be equal to zero\n"

#define FILE_ZERO_SIZE "input file has a zero size\n"

#define HEAP_ZERO_SIZE "input file has a zero size\n"

#define NULL_POINTER "pointer is NULL. "

#define PRINT_ERROR(message)                                \
{                                                           \
    printf("Error: ");                                      \
    printf("%s", message);                                  \
}

#define PRINT_WARNING(message)                              \
{                                                           \
    printf("Warning: ");                                    \
    printf("%s", message);                                  \
}

#define PRINT_HELP()                                        \
{                                                           \
    printf("Usage: huff INPUT_FILE_NAME [-c|-x] OUTPUT_FILE_NAME\n");\
    printf("\nOption:\n");                                  \
    printf("\t-c\tcompress file\n");                        \
    printf("\t-x\textract file\n");                         \
}

#define PRINT_PARAM(param)                                  \
{                                                           \
    PRINT_ERROR(WRONG_OPTION);                              \
    printf(" -%c\n", param);                                \
}

#define PRINT_FILE(file)                                    \
{                                                           \
    printf("File `%s` not found\n", file);                  \
}
