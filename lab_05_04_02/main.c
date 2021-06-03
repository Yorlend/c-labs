#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "product.h"
#include "fileio.h"
#include "constants.h"


int main(int argc, char *argv[])
{
    FILE *f = NULL;

    if (argc < 3)
        return INVALID_CLARGS;

    if (!strcmp(argv[1], "st"))
    {
        FILE *fdest = NULL;
        int exit_code = SUCCESS;
        f = fopen(argv[2], "r");
        fdest = fopen(argv[3], "w");

        exit_code = sort_file(f, fdest);

        if (f != NULL)
            fclose(f);
        if (fdest != NULL)
            fclose(fdest);

        return exit_code;
    }

    if (!strcmp(argv[1], "at"))
    {
        int exit_code;
        product_t input;
        exit_code = read_product(stdin, &input);

        if (!exit_code)
            exit_code = add_unit(argv[2], &input);

        return exit_code;
    }

    return INVALID_CLARGS;
}
