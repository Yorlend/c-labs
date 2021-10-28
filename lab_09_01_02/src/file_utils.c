#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "file_utils.h"
#include "string.h"
#include "float.h"
#include <stdlib.h>

bool file_is_empty(FILE *file)
{
    bool res = false;

    fseek(file, 0, SEEK_END);
    res = ftell(file) == 0;

    rewind(file);
    return res;
}

status_t input_string(FILE *file, char **line)
{
    char *p = NULL;
    size_t len = 0;

    if (getline(line, &len, file) == -1)
    {
        free(*line);
        *line = NULL;
        return input_error;
    }

    if ((p = strchr(*line, '\n')))
        *p = '\0';

    return success;
}

status_t input_double(FILE *file, double *num)
{
    status_t status = success;
    char *buf = NULL;
    char *end_ptr = NULL;

    status = input_string(file, &buf);

    if (status == success)
    {
        *num = strtod(buf, &end_ptr);

        if (*end_ptr != '\0' && *end_ptr != '\n')
            status = input_error;

        free(buf);
    }

    return status;
}
