/**
    @file huff.c

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#include <unistd.h>

#include "option.h"
#include "message.h"

/**
 @brief Main function.

 It's start point of HuffArch

 @return Execution status
*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        PRINT_ERROR(WRONG_INTERFACE);
        return 1;
    }

    if(!handle_params(argc, argv))
        return 0;

    return 1;
}