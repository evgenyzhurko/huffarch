#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "message.h"

#define N 4096
#define N_ALPHA 256

int file_size(FILE *);
int file_close(FILE *);

FILE* file_open(char *, char *);

#define IS_NULL(pointer)                                        \
    do {                                                        \
        if (pointer == NULL)                                    \
        {                                                       \
            PRINT_ERROR(NULL_POINTER);                          \
            printf("File: %s:%u\n", __FILE__, __LINE__);        \
        }                                                       \
    } while(0)


#define FREE_PTR(pointer)                                       \
    do {                                                        \
        if (pointer != NULL)                                    \
        {                                                       \
            free(pointer);                                      \
            pointer = NULL;                                     \
        }                                                       \
    } while(0)
