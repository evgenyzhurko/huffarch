/**
    @file huffman.h

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "heap.h"
#include "utils.h"
#include "binary_tree.h"
#include "code_table.h"

int decode_specific(node_t *, FILE *);
int encode(cell_t *, FILE *, FILE *);
int decode(node_t *, FILE *, FILE *);
int extract(char *, char *);
int compress(char *, char *);