#ifndef __ITEM_H__
#define __ITEM_H__

#include <stdio.h>
#include <stdbool.h>
#include "status_code.h"


typedef struct
{
    const char *name;
    double weight;
    double volume;
} item_t;

bool validate_item(const item_t *item);

bool starts_with(const item_t *item, const char *sub);

double get_density(const item_t *item);

item_t item_null(void);

item_t create_item(const char *name, double weight, double volume);

status_t read_item(FILE *file, item_t *item);

void display_item(FILE *file, const item_t *item);

void destroy_item(item_t *item);

double compare_items(const item_t *item_1, const item_t *item_2);

void swap_items(item_t *item_1, item_t *item_2);

#endif /* __ITEM_H__ */
