#include "option.h"

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

int handle_params(int argc, char *argv[])
{
    int c;
    int out_index = 0;
    int (*function)(char*, char*) = NULL;

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