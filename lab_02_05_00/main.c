#include <stdio.h>

#define N 10
#define SUCCESS 0
#define ERROR 1

int get_size(int *size);
int input_array(int *pbeg, int *pend);
int max_sum(int *pbeg, int *pend);

int main(void)
{
    int exit_code = SUCCESS, size = 0, result = 0;
    int arr[N] = { 0 };
    int *pbeg = arr, *pend = arr;

    exit_code = get_size(&size);
    if (exit_code != ERROR)
    {
        pend += size;
        exit_code = input_array(pbeg, pend);
    }
    if (exit_code != ERROR)
    {
        result = max_sum(pbeg, pend);
        printf("%d\n", result);
    }

    return exit_code;
}

int get_size(int *size)
{
    int exit_code = SUCCESS;
    scanf("%d", size);
    if (*size > N || *size < 1)
        exit_code = ERROR;
    
    return exit_code;
}

int input_array(int *pbeg, int *pend)
{
    int exit_code = SUCCESS;

    for (int *pa = pbeg; pa < pend && exit_code != ERROR; pa++)
        if (scanf("%d", pa) != 1)
            exit_code = ERROR;

    return exit_code;
}

int max_sum(int *pbeg, int *pend)
{
    int tmp = 0, max = *pbeg + *(pend - 1);
    for (int *pb = pbeg + 1, *pe = pend - 2; pb <= pe; pb++, pe--)
    {
        tmp = *pb + *pe;
        if (tmp > max)
            max = tmp; 
    }

    return max;
}
