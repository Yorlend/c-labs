#include "items.h"
#include "file_utils.h"
#include <stdlib.h>


items_t items_null(void)
{
    items_t items = { .data = NULL, .size = 0 };

    return items;
}

status_t allocate_items(FILE *f, items_t *items)
{
    status_t status = success;
    item_t tmp = item_null();
    size_t size = 0;

    while ((status = read_item(f, &tmp)) == success)
    {
        destroy_item(&tmp);
        size++;
    }

    if (feof(f))
        status = success;

    if (status == success)
    {
        items->data = calloc(size, sizeof(item_t));
        if (items->data != NULL)
            items->size = size;
        else
            status = memory_error;
    }

    rewind(f);

    return status;
}

status_t read_items(FILE *f, items_t *items)
{
    status_t status = success;

    if (f == NULL || items == NULL)
        status = file_io_error;
    else if (file_is_empty(f))
        status = file_io_error;

    if (status == success)
        status = allocate_items(f, items);

    if (status == success)
        for (size_t i = 0; status == success && i < items->size; i++)
            status = read_item(f, &items->data[i]);

    if (status != success)
        destroy_items(items);
        
    return status;
}

void destroy_items(items_t *items)
{
    for (size_t i = 0; i < items->size; i++)
        destroy_item(items->data + i);

    free(items->data);
    *items = items_null();
}

void display_items(FILE *f, const items_t *items)
{
    for (size_t i = 0; i < items->size; i++)
        display_item(f, items->data + i);
}

status_t display_items_startswith(FILE *f, const items_t *items, const char *s)
{
    bool flag = false;

    for (size_t i = 0; i < items->size; i++)
    {
        if (starts_with(items->data + i, s))
        {
            display_item(f, items->data + i);
            flag = true;
        }
    }
    
    if (!flag)
        return search_error;
    return success;
}

void sort_items(items_t *items)
{
    for (size_t i = 0; i < items->size; i++)
        for (size_t j = 0; j < items->size - 1; j++)
            if (compare_items(items->data + j, items->data + j + 1) > 0)
                swap_items(items->data + j, items->data + j + 1);
}
