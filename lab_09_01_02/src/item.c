#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "file_utils.h"
#include "item.h"

#define EPS 1e-6


bool validate_item(const item_t *item)
{
    if (item == NULL || item->name == NULL)
        return false;

    int len = strlen(item->name);
    bool flag = false;

    for (int i = 0; i < len; i++)
        if (!isspace(item->name[i]))
            flag = true;

    return flag && len > 0 && item->volume > 0 && item->weight > 0;
}

double get_density(const item_t *item)
{
    if (item == NULL || fabs(item->volume) < EPS)
        return nan("");
    return item->weight / item->volume;
}

item_t item_null(void)
{
    item_t res = { .name = NULL, .volume = 0.0, .weight = 0.0 };
    return res;
}

item_t create_item(const char *name, double weight, double volume)
{
    if (name == NULL || strlen(name) == 0)
        return item_null();

    item_t res = item_null();

    res.name = strdup(name);
    res.weight = weight;
    res.volume = volume;

    return res;
}

status_t read_item(FILE *file, item_t *item)
{
    status_t status = success;
    char *name = NULL;
    double weight = 0.0, volume = 0.0;

    if (input_string(file, &name) != success ||
        input_double(file, &weight) != success ||
        input_double(file, &volume) != success)
        status = input_error;

    if (status != success && name != NULL)
        free(name);

    if (status == success)
    {
        *item = create_item(name, weight, volume);
        free(name);
    }

    if (!validate_item(item))
    {
        destroy_item(item);
        status = input_error;
    }

    return status;
}

void display_item(FILE *file, const item_t *item)
{
    fprintf(file, "%s\n", item->name);
    fprintf(file, "%.6lf\n", item->weight);
    fprintf(file, "%.6lf\n", item->volume);
}

void destroy_item(item_t *item)
{
    if (item != NULL && item->name != NULL)
    {
        free((void*)item->name);
        *item = item_null();
    }
}

bool starts_with(const item_t *item, const char *sub)
{
    if (sub == NULL || strlen(item->name) < strlen(sub))
        return false;

    for (int i = 0; *sub; i++, sub++)
        if (item->name[i] != *sub)
            return false;

    return true;
}

double compare_items(const item_t *item_1, const item_t *item_2)
{
    double density_1 = get_density(item_1);
    double density_2 = get_density(item_2);

    return density_1 - density_2;
}

void swap_items(item_t *item_1, item_t *item_2)
{
    item_t temp = *item_1;
    *item_1 = *item_2;
    *item_2 = temp;
}
