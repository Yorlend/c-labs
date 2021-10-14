#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>
#include <stdbool.h>


typedef struct
{
    int *data;
    size_t size;
} array_t;


array_t create_array(size_t size);
array_t pack_array(int *begin, int *end);
void destroy_array(array_t *array);

bool array_valid(const array_t *array);

int *array_begin(array_t *array);
int *array_end(array_t *array);

#endif // __ARRAY_H__
