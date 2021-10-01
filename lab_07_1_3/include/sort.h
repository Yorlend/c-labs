#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>


void mysort(void *base, size_t nitems, size_t size, \
int (*compar)(const void *, const void *));

#endif // __SORT_H__
