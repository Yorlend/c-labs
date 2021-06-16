#include "fileio.h"
#include "product.h"
#include "constants.h"
#include <stdlib.h>

/**
 * compares two product_t structs by price
 * 
 * \param[in] a first struct pointer
 * \param[in] b second struct pointer
 * 
 * \return 0 if a and b are equal, negative if a is less, positive otherwise
 */
static int product_compare(const void *a, const void *b)
{
    product_t *prod_a = (product_t *)a;
    product_t *prod_b = (product_t *)b;

    int res = (int)(prod_b->price - prod_a->price);
    if (res == 0)
        res = (int)(prod_b->quantity - prod_a->quantity);

    return res;
}

/**
 * swaps two structures
 * 
 * \param[in] a first struct to swap
 * \param[in] b second struct to swap
 */
static void swap(product_t *a, product_t *b)
{
    product_t tmp = *a;
    *a = *b;
    *b = tmp;
}

static void insert_product(product_t *arr, int *size, product_t *unit)
{
    int flag = 0;
    arr[*size] = *unit;
    (*size)++;
    for (int i = 0; i < *size; i++)
    {
        if (flag == 0 && product_compare(&arr[i], unit) > 0)
            flag = 1;

        if (flag)
            swap(&arr[i], unit);
    }
}

/**
 * Sorts a given file with product structs by price and writes it to  
 * another file
 * 
 * \param[in] fsrc source file
 * \param[out] fdest destination file
 * 
 * \return ERROR CODE
 */
int sort_file(FILE *fsrc, FILE *fdest)
{
    if (fsrc == NULL || fdest == NULL)
        return INVALID_FILE;

    product_t goods[MAX_GOODS_AMOUNT] = { 0 };
    int size = 0;

    if (read_file(fsrc, goods, &size))
       return INVALID_DATA;
    
    qsort(goods, (size_t) size, sizeof(product_t), product_compare);

    write_file(fdest, goods, size);

    return SUCCESS;
}

/**
 * Adds a product unit to the given file, maintaining the sorted order
 * 
 * \param[in] filename name of the file of structs
 * 
 * \return ERROR CODE
 */
int add_unit(char *filename)
{
    int exit_code = SUCCESS;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        exit_code = INVALID_FILE;

    product_t goods[MAX_GOODS_AMOUNT + 1];
    int size = 0;

    if (!exit_code)
        if (read_file(f, goods, &size))
            exit_code = INVALID_DATA;

    if (f != NULL)
        fclose(f);

    product_t prod_in;
    if (!exit_code)
        exit_code = read_product(stdin, &prod_in);

    if (!exit_code)
    {
        insert_product(goods, &size, &prod_in);

        f = fopen(filename, "w");
        exit_code = write_file(f, goods, size);

        if (f != NULL)
            fclose(f);
    }

    return exit_code;
}
