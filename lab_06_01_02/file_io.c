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
        return input_error;

    *p = '\0';

    return success;
}

status_t input_double(FILE *file, double *num)
{
    char buf[DIG_MAX];
    char *end_ptr = NULL;

    if (input_string(file, buf, DIG_MAX) != success)
        return input_error;

    *num = strtod(buf, &end_ptr);

    if (*end_ptr != 0)
        return input_error;

    return success;
}

status_t read_item(FILE *file, item_t *item)
{
    if (input_string(file, item->name, STR_MAX) != success \
        || input_double(file, &item->weight) \
        || input_double(file, &item->volume))
        return input_error;

    if (!validate_item(item))
        return input_error;

    return success;
}

status_t read_items(FILE *file, item_t *items, int *n)
{
    status_t status = success;
    *n = 0;

    if (file_is_empty(file))
        return file_io_error;

    while (!feof(file) && status == success)
    {
        if (*n >= STRUCT_MAX)
            return file_io_error;
        status = read_item(file, &items[*n]);
        if (status == success)
            ++*n;
    }

    if (feof(file))
        return success;
    
    return status;
}

void display_item(FILE *file, const item_t *item)
{
    fprintf(file, "%s\n", item->name);
    fprintf(file, "%.6lf\n", item->weight);
    fprintf(file, "%.6lf\n", item->volume);
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
        return search_error;
    return success;
}
