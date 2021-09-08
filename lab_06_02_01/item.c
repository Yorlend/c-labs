#include "item.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>


bool validate_item(const item_t *item)
{
    int len = strlen(item->name);
    bool flag = false;

    for (int i = 0; i < len; i++)
        if (!isspace(item->name[i]))
            flag = true;

    return flag && len > 0 && item->volume > 0 && item->weight > 0;
}

double get_density(const item_t *item)
{
    return item->weight / item->volume;
}

bool starts_with(const item_t *item, const char *sub)
{
    if (strlen(item->name) < strlen(sub))
        return false;

    for (int i = 0; *sub; i++, sub++)
        if (item->name[i] != *sub)
            return false;

    return true;
}

int compare_items(const item_t *item_1, const item_t *item_2)
{
    double density_1 = get_density(item_1);
    double density_2 = get_density(item_2);

    return density_1 < density_2;
}

void swap_items(item_t *item_1, item_t *item_2)
{
    item_t temp = *item_1;
    *item_1 = *item_2;
    *item_2 = temp;
}

void sort_items(item_t *items, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (compare_items(&items[j], &items[j + 1]) <= 0)
                swap_items(&items[j], &items[j + 1]);
}
