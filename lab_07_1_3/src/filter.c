#include "filter.h"
#include "status.h"
#include <stdlib.h>


static const int *get_last_neg(const int *pb_src, const int *pe_src)
{
    const int *pe_tmp = pe_src;

    while (pe_tmp-- > pb_src)
        if (*pe_tmp < 0)
            return pe_tmp;
    
    return pe_src;
}

static void mem_copy(void *dst, const void *src, size_t n)
{
    const char *ps = src;
    for (char *pd = dst; n-- != 0; pd++, ps++)
        *pd = *ps;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_dst == NULL || pe_dst == NULL)
        return func_args_error;

    if (pb_src == pe_src)
        return empty_array_error;

    int size = get_last_neg(pb_src, pe_src) - pb_src;

    if (size == 0)
        return filter_error;

    *pb_dst = malloc((unsigned)size * sizeof(int));

    if (*pb_dst == NULL)
        return mem_error;
    
    *pe_dst = *pb_dst + size;

    mem_copy(*pb_dst, pb_src, (unsigned)size * sizeof(int));

    return success;
}

status_t filter(array_t *array)
{
    if (array == NULL || !array_valid(array))
        return func_args_error;
    
    int *b_src = array_begin(array);
    int *e_src = array_end(array);
    int *b_dst, *e_dst;
    status_t exit_code = key(b_src, e_src, &b_dst, &e_dst);

    if (exit_code == success)
    {
        destroy_array(array);
        *array = pack_array(b_dst, e_dst);
    }

    return exit_code;
}
