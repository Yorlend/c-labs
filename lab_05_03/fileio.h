#ifndef _FILEIO_H
#define _FILEIO_H

#include <stdio.h>

int create_file(char *filename, int quantity);
int output_file(FILE *f);
int get_quantity(FILE *f, size_t *size);

#endif