#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "file_utils.h"
#include <stdlib.h>
#include <string.h>
#include <float.h>

bool file_is_empty(FILE *file)
{
    bool res = false;

    fseek(file, 0, SEEK_END);
    res = ftell(file) == 0;

    rewind(file);
    return res;
}

int input_string(FILE *file, char **line)
{
    char *p = NULL;
    size_t len = 0;

    if (getline(line, &len, file) == -1)
    {
        free(*line);
        *line = NULL;
        return EXIT_FAILURE;
    }

    if ((p = strchr(*line, '\n')))
        *p = '\0';

    return EXIT_SUCCESS;
}

int input_int(FILE *file, int *num)
{
    char *buf = NULL;
    char *end_ptr = NULL;

    int status = input_string(file, &buf);

    if (status == EXIT_SUCCESS)
    {
        *num = strtol(buf, &end_ptr, 10);

        if (*end_ptr != '\0' && *end_ptr != '\n')
            status = EXIT_FAILURE;

        free(buf);
    }

    return status;
}
