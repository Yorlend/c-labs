#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include "status_code.h"
#include "item.h"
#include <stdio.h>
#include <stdbool.h>


bool file_is_empty(FILE *file);

status_t input_string(FILE *file, char **str);

status_t input_double(FILE *file, double *num);

#endif /* __FILE_UTILS_H__ */
