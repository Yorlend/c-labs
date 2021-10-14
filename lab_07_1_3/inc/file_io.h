#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include <stdio.h>
#include "status.h"
#include "array.h"


void output_sort_data(const char *filename, size_t size, double time);

status_t input_array_fp(FILE *file, array_t *array);
status_t output_array_fp(FILE *file, array_t *array);

status_t input_array(const char *filename, array_t *array);
status_t output_array(const char *filename, array_t *array);


#endif // __FILE_IO_H__
