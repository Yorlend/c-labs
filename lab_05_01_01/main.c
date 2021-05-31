#include <stdlib.h>
#include "fileio.h"


int main(void)
{
    int max1, max2;

    int result = process(stdin, &max1, &max2);
    if (result == EXIT_SUCCESS)
        printf("%d %d\n", max1, max2);

    return result;
}
