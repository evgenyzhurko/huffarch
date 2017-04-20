#pragma once

#include <stdio.h>
#include <stdint.h>

#include "heap.h"
#include "utils.h"
#include "binary_tree.h"
#include "code_table.h"

int encode(struct cell_t *, FILE *, FILE *);
int decode(struct node_t *, FILE *, FILE *);
int extract(char *, char *);
int compress(char *, char *);