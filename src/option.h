/**
    @file option.h

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma once

#include "message.h"
#include "huffman.h"

extern char *optarg;
extern int optind, optopt, opterr;

int handle_params(int argc, char *argv[]);