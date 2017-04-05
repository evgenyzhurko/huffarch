#pragma once

#include "message.h"
#include "huffman.h"

extern char *optarg;
extern int optind, optopt, opterr;

int handle_params(int argc, char *argv[]);