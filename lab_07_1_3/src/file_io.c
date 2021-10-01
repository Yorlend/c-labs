#include "file_io.h"
#include <string.h>



static status_t empty_file(FILE *f)
{
    fseek(f, 0, 2);
    if (ftell(f) == 0)
        return file_error;

    rewind(f);
    return success;
}

static void close_file(FILE *f)
{
    if (f != NULL)
        fclose(f);
}
static status_t array_io(const char *filename, const char *mode, \
array_t *array)
{
    status_t exit_code = success;

    if (filename == NULL)
        exit_code = func_args_error;

    FILE *file = fopen(filename, mode);

    if (exit_code == success && !strcmp(mode, "r"))
        exit_code = input_array_fp(file, array);

    if (exit_code == success && !strcmp(mode, "w"))
        exit_code = output_array_fp(file, array);

    close_file(file);

    return exit_code;
}

static status_t count_items(FILE *file, size_t *counter)
{
    if (file == NULL || counter == NULL)
        return func_args_error;

    int tmp = 0;
    *counter = 0;
    rewind(file);

    while (!feof(file))
        if (fscanf(file, "%d", &tmp) == 1)
            (*counter)++;
        else if (!feof(file))
            return input_error;

    rewind(file);
    return success;
}

void output_sort_data(const char *filename, size_t size, double time)
{
    FILE *f = fopen(filename, "a");

    if (f != NULL)
        fprintf(f, "%zu %lf\n", size, time);

    if (f != NULL)
        fclose(f);
}

status_t input_array_fp(FILE *file, array_t *array)
{
    size_t size;
    status_t exit_code = success;

    if (file == NULL)
        exit_code = file_error;

    if (exit_code == success)
        exit_code = empty_file(file);

    if (exit_code == success)
        exit_code = count_items(file, &size);

    if (exit_code == success)
    {
        *array = create_array(size);
        if (!array_valid(array))
            exit_code = mem_error;
    }

    if (exit_code == success)
    {
        int *iter = array_begin(array);
        int *end = array_end(array);
        while (iter != end)
            if (fscanf(file, "%d", iter++) != 1)
                exit_code = input_error;
    }

    return exit_code;
}

status_t output_array_fp(FILE *file, array_t *array)
{
    if (file == NULL || !array_valid(array))
        return func_args_error;
    
    int *iter = array_begin(array);
    int *end = array_end(array);
    while (iter != end)
        fprintf(file, "%d\n", *iter++);

    return success;
}

status_t input_array(const char *filename, array_t *array)
{
    return array_io(filename, "r", array);
}

status_t output_array(const char *filename, array_t *array)
{
    return array_io(filename, "w", array);
}
