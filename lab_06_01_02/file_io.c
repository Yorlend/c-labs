#include "file_io.h"
#include "string.h"
#include "float.h"
#include <stdlib.h>

bool file_is_empty(FILE *file)
{
    bool res = false;

    fseek(file, 0, SEEK_END);
    res = ftell(file) == 0;

    rewind(file);
    return res;
}

status_t input_string(FILE *file, char *str, int buf_size)
{
    char *p = NULL;

    if (!fgets(str, buf_size, file) || !(p = strchr(str, '\n')))
        return INPUT_ERROR;

    *p = '\0';

    return SUCCESS;
}

status_t input_double(FILE *file, double *num)
{
    char buf[DBL_MAX_10_EXP + 2];

    if (input_string(file, buf, DBL_MAX_10_EXP + 2) != SUCCESS)
        return INPUT_ERROR;

    *num = atof(buf);

    return SUCCESS;
}

status_t read_item(FILE *file, item_t *item)
{
    if (input_string(file, item->name, STR_MAX) != SUCCESS \
        || input_double(file, &item->weight) \
        || input_double(file, &item->volume))
        return INPUT_ERROR;

    if (!validate_item(item))
        return INPUT_ERROR;

    return SUCCESS;
}

status_t read_items(FILE *file, item_t *items, int *n)
{
    status_t status = SUCCESS;
    *n = 0;

    if (file_is_empty(file))
        return FILE_IO_ERROR;

    while (!feof(file) && status == SUCCESS)
    {
        status = read_item(file, &items[*n]);
        if (status == SUCCESS)
            ++*n;
    }

    if (feof(file))
        return SUCCESS;
    
    return status;
}

void display_item(FILE *file, const item_t *item)
{
    fprintf(file, "%s\n%lf\n%lf\n", item->name, item->weight, item->volume);
}

void display_items(FILE *file, const item_t *items, int n)
{
    for (int i = 0; i < n; i++)
        display_item(file, &items[i]);
}

status_t display_startswith(FILE *file, const item_t *items, int n, \
    const char *sub)
{
    bool flag = false;

    for (int i = 0; i < n; i++)
        if (starts_with(&items[i], sub))
        {
            display_item(file, &items[i]);
            flag = true;
        }
    
    if (!flag)
        return SEARCH_ERROR;
    return SUCCESS;
}
