#ifndef FILE_IO_H
#define FILE_IO_H

#include "status_code.h"
#include "item.h"
#include <stdio.h>
#include <stdbool.h>


bool file_is_empty(FILE *file);

status_t input_string(FILE *file, char *str, int buf_size);
status_t input_double(FILE *file, double *num);

status_t read_item(FILE *file, item_t *item);
status_t read_items(FILE *file, item_t *items, int *n);

void display_item(FILE *file, const item_t *item);
void display_items(FILE *file, const item_t *items, int n);

status_t display_startswith(FILE *file, const item_t *items, int n, \
const char *sub);

#endif // FILE_IO_H
