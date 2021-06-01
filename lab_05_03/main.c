/**
 * Lab 5 / Problem 3
 * 
 * each function is documented (doxygen style)
 * sorting is implemented through `sort_file` function
 * in `file_process.h` header file.
 * (Selection Sort)
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileio.h"
#include "file_process.h"


int main(int argc, char *argv[])
{
    FILE *f = NULL;

    if (argc < 3)
        return EXIT_FAILURE;

    if (!strcmp(argv[1], "c"))
        return create_file(argv[3], atoi(argv[2]));

    if (!strcmp(argv[1], "p"))
    {
        int exit_code = EXIT_SUCCESS;
        f = fopen(argv[2], "rb");
        exit_code = output_file(f);
        if (f != NULL)
            fclose(f);
        return exit_code;
    }

    if (!strcmp(argv[1], "s"))
    {
        int exit_code = EXIT_SUCCESS;
        f = fopen(argv[2], "rb+");
        exit_code = sort_file(f);
        if (f != NULL)
            fclose(f);
        return exit_code;
    }

    return EXIT_FAILURE;
}