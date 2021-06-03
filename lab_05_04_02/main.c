#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "product.h"
#include "fileio.h"
#include "constants.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
        return INVALID_CLARGS;

    if (!strcmp(argv[1], "st"))
    {
        if (argc < 4)
            return INVALID_CLARGS;

        if (!strcmp(argv[2], argv[3]))
            return INVALID_CLARGS;

        FILE *f = fopen(argv[2], "r");
        FILE *fdest = fopen(argv[3], "w");

        int exit_code = sort_file(f, fdest);

        if (f != NULL)
            fclose(f);
        if (fdest != NULL)
            fclose(fdest);

        return exit_code;
    }

    if (!strcmp(argv[1], "at"))
    {
        if (argc < 3)
            return INVALID_CLARGS;

        product_t input;
        int exit_code = read_product(stdin, &input);

        if (!exit_code)
            exit_code = add_unit(argv[2], &input);

        return exit_code;
    }

    return INVALID_CLARGS;
}
