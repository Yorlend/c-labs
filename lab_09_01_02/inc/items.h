#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "item.h"
#include "status_code.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>


typedef struct 
{
    item_t *data;
    size_t size;
} items_t;


items_t items_null(void);

status_t allocate_items(FILE *f, items_t *items);

status_t read_items(FILE *f, items_t *items);

void destroy_items(items_t *items);

void display_items(FILE *f, const items_t *items);

status_t display_items_startswith(FILE* f, const items_t *items, const char *s);

void sort_items(items_t *items);

#endif /* __ITEMS_H__ */
