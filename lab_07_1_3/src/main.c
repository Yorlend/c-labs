#include <stdio.h>
#include <string.h>
#include "status.h"
#include "array.h"
#include "file_io.h"
#include "sort.h"
#include "filter.h"


static int cmp_int(const void *i1, const void *i2)
{
    return *(int*)i1 - *(int*)i2;
}

int main(int argc, char *argv[])
{
    array_t array = { 0 };
    status_t exit_code = success;

    if (argc < 3)
        exit_code = args_error;


    if (exit_code == success)
        exit_code = input_array(argv[1], &array);
    
    if (argc == 4)
    {
        if (!strcmp(argv[3], "f"))
            exit_code = filter(&array);
        else
            exit_code = args_error;
    }

    if (exit_code == success)
        mysort(array_begin(&array), array.size, sizeof(int), cmp_int);

    #ifndef SORT_TIME
    if (exit_code == success)
        exit_code = output_array(argv[2], &array);
    #endif

    destroy_array(&array);
    return exit_code;
}
