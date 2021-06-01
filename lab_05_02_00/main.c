#include <stdio.h>
#include <stdlib.h>
#include "file_process.h"


int main(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    double res = 0.0;
    FILE *file = NULL;

    if (argc < 2)
        exit_code = EXIT_FAILURE;

    if (!exit_code)
    {
        file = fopen(argv[1], "r");
        exit_code = process(file, &res);
        if (file != NULL)
            fclose(file);
    }

    if (!exit_code)
        printf("%lf\n", res);
    
    return exit_code;
}