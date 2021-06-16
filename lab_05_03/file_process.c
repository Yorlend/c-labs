#include "file_process.h"
#include "fileio.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Works with rb filemode
 */
int get_number_by_pos(FILE *file, int *num, size_t pos)
{
    int rc = 1;
    if (file == NULL)
        return EXIT_FAILURE;

    fseek(file, (int) (pos * sizeof(int)), SEEK_SET);
    rc = fread(num, sizeof(int), 1, file);   
    if (rc != 1 || rc == EOF)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * Works with rb+ filemode
 */
int put_number_by_pos(FILE *file, int num, size_t pos)
{
    if (file == NULL)
        return EXIT_FAILURE;

    fseek(file, (int) (pos * sizeof(int)), SEEK_SET);

    if (fwrite(&num, sizeof(int), 1, file) != 1)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * implements selection sort for binary files with integer values
 */
int sort_file(FILE *file)
{
    if (file == NULL)
        return EXIT_FAILURE;

    size_t size = 0;
    int exit_code = EXIT_SUCCESS;
    exit_code = get_quantity(file, &size);

    if (size < 1)
        return EXIT_FAILURE;

    int num = 0, first = 0;
    for (size_t i = 0; i < size; i++)
    {
        int min;
        size_t k = i;
        get_number_by_pos(file, &min, i);
        first = min;
        for (size_t j = i; j < size; j++)
        {
            get_number_by_pos(file, &num, j);
            if (num < min)
            {
                min = num;
                k = j;
            }
        }
        put_number_by_pos(file, first, k);
        put_number_by_pos(file, min, i);
    }

    return exit_code;
}
