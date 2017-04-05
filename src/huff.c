#include <unistd.h>

#include "option.h"
#include "message.h"

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