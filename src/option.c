/**
    @file option.c

    @author Evgeny Zhurko
    @copyright Copyright (c) 2016, Evgeny Zhurko.
    @license This file is released under the MIT Licesne.
*/

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

#include "option.h"

/**
 @brief Check command line argument

 Check arguments for getopt params.

 @param[in] index Position of current parameter
 @param[in] out_index End status
 @return Execution status
*/
int check_arguments(int index, int out_index)
{
    if (out_index != 0)
    {
        PRINT_ERROR(CONTRADICTORY_OPTION);
        return 1;
    }
    if (index < 3)
    {
        PRINT_ERROR(WRONG_INTERFACE);
        return 1;
    }
    return 0;
}

/**
 @brief Handle command line arguments.

 Check and handle getopt parameters.

 @param[in] argc Number of arguments
 @param[in] argv Array of arguments
 @return Execution status
*/
int handle_params(int argc, char *argv[])
{
    int c;
    int out_index = 0;
    int (*function)(char *, char *) = NULL;

    opterr = 0;

    while ((c = getopt(argc, argv, "hx:c:")) != -1)
    {
        switch (c)
        {
            case 'x':
                if (!check_arguments(optind - 1, out_index))
                {
                    function = extract;
                    out_index = optind - 1;
                    break;
                }
                return 1;
            case 'c':
                if (!check_arguments(optind - 1, out_index))
                {
                    function = compress;
                    out_index = optind - 1;
                    break;
                }
                return 1;
            case 'h':
                PRINT_HELP();
                return 0;
            case '?':
            default:
                PRINT_PARAM(optopt);
                return 1;
        }
    }

    if (!function(argv[out_index], argv[2]))
    {
        return 0;
    }

    return 1;
} 