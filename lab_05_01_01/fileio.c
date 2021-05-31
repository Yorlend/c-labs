#include "fileio.h"
#include <stdlib.h>


static void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int process(FILE *file, int *max1, int *max2)
{
    if (!file)
        return EXIT_FAILURE;
    
    fseek(file, 0, SEEK_SET);

    int curr_max, prev_max;
    if (fscanf(file, "%d%d", &curr_max, &prev_max) <= 1)
        return EXIT_FAILURE;
    
    if (curr_max < prev_max)
        swap(&prev_max, &curr_max);

    int curr_num;
    while (fscanf(file, "%d", &curr_num) > 0)
    {
        if (curr_num > prev_max)
        {
            if (curr_num > curr_max)
            {
                swap(&curr_max, &prev_max); 
                swap(&curr_num, &curr_max);
            }
            else
                swap(&curr_num, &prev_max);
        }
    }

    *max1 = curr_max;
    *max2 = prev_max;

    return EXIT_SUCCESS;
}
