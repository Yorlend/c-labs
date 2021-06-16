#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

/**
 * outputs the whole file on the screen
 * 
 * \param[in] f file to output
 * 
 * \return ERROR CODE
 * 
 * \details the file is expected to be open in rb mode
 */
int output_file(FILE *f)
{
    if (f == NULL)
        return EXIT_FAILURE;

    size_t size = 0;
    get_quantity(f, &size);
    
    if (size < 1)
        return EXIT_FAILURE;

    int num = 0;

    while (1)
    {
        if (fread(&num, sizeof(int), 1, f) != 1)
            break;
        printf("%d ", num);
    }
    printf("\n");

    return EXIT_SUCCESS;
}

/**
 * creates new binary file
 * \param[in] filename name of the desired file
 * \param[in] quantity quantity of elements in a file
 * 
 * \return ERROR CODE
 * 
 * \details Creates a file named filename with a set amount of random elements
 * defined by the quantity value.
 */
int create_file(char *filename, int quantity)
{
    FILE *f = fopen(filename, "wb");
    int num = 0;

    if (quantity < 1)
        return EXIT_FAILURE;

    for (int i = 0; i < quantity; i++)
    {
        num = rand() % 201 - 100;
        if (fwrite(&num, sizeof(int), 1, f) != 1)
            return EXIT_FAILURE;
    }

    fclose(f);

    return EXIT_SUCCESS;
}

/**
 * calculates the number of integers in a given binary file
 * 
 * \param[in] f binary file
 * \param[out] size number of integers in a file
 * 
 * \return ERROR CODE
 */
int get_quantity(FILE *f, size_t *size)
{
    if (f == NULL)
        return EXIT_FAILURE;
    
    fseek(f, 0, SEEK_END);
    *size = (unsigned long) ftell(f) / sizeof(int);
    fseek(f, 0, SEEK_SET);

    return EXIT_SUCCESS;
}
