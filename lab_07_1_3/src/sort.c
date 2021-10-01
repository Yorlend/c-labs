#include "sort.h"
#include "file_io.h"
#include <time.h>
#include <stdlib.h>


static void swap(void *elem1, void *elem2, size_t size)
{
    char tmp = *(char*)elem1;
    *(char*)elem1 = *(char*)elem2;
    *(char*)elem2 = tmp;
    if (size > 1)
        swap((char*)elem1 + 1, (char*)elem2 + 1, size - 1);
}

void mysort(void *base, size_t nitems, size_t size, \
int (*compar)(const void *, const void *))
{
    size_t barrier = nitems;

    #ifdef SORT_TIME
    
    clock_t t = clock();

    #endif

    #ifdef QSORT

    qsort(base, nitems, size, compar);

    #else

    do
    {
        size_t new_barrier = 0;
        for (size_t i = 0; i + 1 < barrier; i++)
        {
            void *elem_1 = (char*)base + i * size;
            void *elem_2 = (char*)base + (i + 1) * size;

            if (compar(elem_1, elem_2) > 0)
            {
                swap(elem_1, elem_2, size);
                new_barrier = i + 1;
            }
        }
        barrier = new_barrier;
    }
    while (barrier > 0);

    #endif

    #ifdef SORT_TIME

    t = clock() - t;
    double timing = ((double)t) / CLOCKS_PER_SEC;

    output_sort_data("qout.txt", nitems, timing);

    #endif
}
