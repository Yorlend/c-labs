#ifndef _FILEIO_H
#define _FILEIO_H

#include <stdio.h>
#include "product.h"

#define MAX_ARR_SIZE 1000


int read_file(FILE *file, product_t *res, int *size);
int write_file(FILE *file, product_t *res, int size);
int read_product(FILE *file, product_t *prod);

#endif
