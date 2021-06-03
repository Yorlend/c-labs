#include "fileio.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/**
 * Reads a line from a file
 * 
 * \param[in] file target file
 * \param[out] str resulting line
 * 
 * \return ERROR CODE
 */
static int input_string(FILE *file, char *str, int buf)
{
    if (file == NULL)
        return INVALID_FILE;

    if (fgets(str, buf, file) == NULL)
        return INVALID_DATA;

    while (isspace(*str++));
    if (*str == '\0')
        return INVALID_DATA;

    for (char *c = str; *c != '\0'; c++)
        if (*c == '\n')
        {
            *c = '\0';
            return SUCCESS;
        }

    return INVALID_DATA;
}

/**
 * Converts a line from a file to a uint32_t
 * 
 * \param[in] file target file
 * \param[out] price resulting uint32_t
 * 
 * \return ERROR CODE
 */
static int input_price(FILE *file, uint32_t *price)
{
    if (file == NULL)
        return INVALID_FILE;

    char tmp[MAX_STR_LEN];
    char *ptr = NULL;
    if (input_string(file, tmp, MAX_STR_LEN))
        return INVALID_DATA;

    *price = strtoul(tmp, &ptr, NUM_BASE);

    if (*price == 0)
        return INVALID_DATA;
    
    if (*ptr)
        return INVALID_DATA;

    return SUCCESS;
}

/**
 * Reads structs from a file to an array of structs
 * 
 * \param[in] file file of structs
 * \param[out] res array of structs
 * \param[out] size size of res
 * 
 * \return ERROR CODE
 */
int read_file(FILE *file, product_t *res, int *size)
{
    if (file == NULL)
        return INVALID_FILE;
    *size = 0;
    int exit_code = SUCCESS;

    while (!(exit_code = read_product(file, &res[*size])))
        (*size)++;

    if (feof(file) && exit_code != INVALID_UINT)
        exit_code = SUCCESS;

    if (*size == 0)
        exit_code = INVALID_FILE;

    return exit_code;
}

/**
 * Reads one struct from a file
 * 
 * \param[in] file file of structs
 * \param[out] prod resulting struct
 * 
 * \return ERROR CODE
 */
int read_product(FILE *file, product_t *prod)
{
    if (file == NULL)
        return INVALID_FILE;

    char unit_name[MAX_STR_LEN];
    char manufacturer[MAX_MAN_LEN];
    uint32_t unit_price = 0;
    uint32_t unit_quant = 0;
    
    if (input_string(file, unit_name, MAX_STR_LEN))
        return INVALID_DATA;
    if (input_string(file, manufacturer, MAX_MAN_LEN))
        return INVALID_DATA;
    if (input_price(file, &unit_price))
        return INVALID_UINT;
    if (input_price(file, &unit_quant))
        return INVALID_UINT;

    strcpy(prod->name, unit_name);
    strcpy(prod->manufacturer, manufacturer);
    prod->price = unit_price;
    prod->quantity = unit_quant;


    return SUCCESS;
}

int write_file(FILE *file, product_t *res, int size)
{
    if (file == NULL)
        return INVALID_FILE;

    if (size < 1)
        return INVALID_DATA;

    for (int i = 0; i < size; i++)
    {
        if (fprintf(file, "%s\n%s\n%u\n%u\n", res[i].name, \
        res[i].manufacturer, res[i].price, res[i].quantity) < 0)
            return INVALID_DATA;
    }
    return SUCCESS;
}
