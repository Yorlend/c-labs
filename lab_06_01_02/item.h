#ifndef ITEM_H
#define ITEM_H

#include "constants.h"
#include <stdbool.h>


typedef struct
{
    char name[STR_MAX];
    double weight;
    double volume;
} item_t;

bool validate_item(const item_t *item);
bool starts_with(const item_t *item, const char *sub);

double get_density(const item_t *item);

double compare_items(const item_t *item_1, const item_t *item_2);
void swap_items(item_t *item_1, item_t *item_2);
void sort_items(item_t *items, int n);

#endif // ITEM_H
