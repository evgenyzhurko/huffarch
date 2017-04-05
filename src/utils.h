#pragma once

#include <stdio.h>

#include "message.h"

int file_size(FILE *);
int file_close(FILE *);

FILE* file_open(char *, char *);
