#include "file_IO.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    int exit_code = SUCCESS;
    FILE* fp = NULL;

    if (argc > 1)
        exit_code = create_bin(fp, argv[1]);
    else
        exit_code = FILE_ERROR;

    if (!exit_code)
        exit_code = process_bin(fp, argv[1]);

    if (!exit_code)
    {
        #ifdef DETAILED_OUTPUT
        printf("Измененный файл:\n");
        #endif
        exit_code = read_bin(fp, argv[1]);
    }

    return exit_code;
}
