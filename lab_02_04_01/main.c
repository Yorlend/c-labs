#include <stdio.h>

#define N 10
#define SUCCESS 0
#define ERROR 1
#define OVERFLOW 100

int input_arr(int *arr);
void output_arr(int *arr, int size);
void insertion_sort(int *arr, int size);

int main(void)
{
    int exit_code = SUCCESS;
    int size, arr[N] = { 0 };

    size = input_arr(arr);
    if (size == 0)
        exit_code = ERROR;
    if (size == OVERFLOW)
    {
        size = N;
        exit_code = OVERFLOW;
    }

    if (exit_code != ERROR)
    {
        insertion_sort(arr, size);

        output_arr(arr, size);
    }

    return exit_code;
}

int input_arr(int *arr)
{
    int i = 0, exit = 1, tmp = 0;
    while (exit && (i < 10))
    {
        if (scanf("%d", &arr[i]))
            i++;
        else
            exit = 0;
    }

    if (scanf("%d", &tmp) != 1)
        return 0;
    
    if (exit && i != 0)
        return OVERFLOW;
    return i;
}

void output_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d\n", arr[i]);
}

void insertion_sort(int *arr, int size)
{
    int tmp, j;

    for (int i = 1; i < size; i++)
    {
        tmp = arr[i];
        j = i - 1;

        while (j > -1 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = tmp;
    }
}