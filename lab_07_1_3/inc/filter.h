#ifndef __FILTER_H__
#define __FILTER_H__

#include "status.h"
#include "array.h"


int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
status_t filter(array_t *array);

#endif // __FILTER_H__
