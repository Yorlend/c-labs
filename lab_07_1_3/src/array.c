#include <stdlib.h>
#include "array.h"


array_t create_array(size_t size)
{
    array_t result = { 0 };

    if (size > 0)
    {
        result.data = calloc(size, sizeof(int));
        if (result.data != NULL)
            result.size = size;
    }

    return result;
}

array_t pack_array(int *begin, int *end)
{
    if (begin == NULL || end == NULL || begin >= end)
        return create_array(0);
    
    array_t result = { 0 };
    result.data = begin;
    result.size = (unsigned)(end - begin);

    return result;
}

void destroy_array(array_t *array)
{
    if (array_valid(array))
    {
        free(array->data);
        array->data = NULL;
        array->size = 0;
    }
}

bool array_valid(const array_t *array)
{
    return array->size > 0;
}

int *array_begin(array_t *array)
{
    return array->data;
}

int *array_end(array_t *array)
{
    return array->data + array->size;
}
