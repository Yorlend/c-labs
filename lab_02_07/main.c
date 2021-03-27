#include <stdio.h>

#define N 1000000
#define SUCCESS 0
#define ERROR 1

int input_array(int *arr, int *size);
void output_arr(int *arr, int size);
void insertion_sort(int *arr, int size);

int main(void)
{
    int exit_code = SUCCESS;
    int size, arr[N] = { 0 };

    input_array(arr, &size);
    if (size == 0)
        exit_code = ERROR;

    if (exit_code != ERROR)
    {
        insertion_sort(arr, size);

        output_arr(arr, size);
    }

    return exit_code;
}

int input_array(int *arr, int *size)
{
    int tmp = 0, exit_code = SUCCESS, rc = 0;
    rc = scanf("%d", size);
    if (!rc)
        exit_code = ERROR;
    if (*size > N || *size < 1)
        exit_code = ERROR;
    for (int i = 0; i < *size && exit_code == SUCCESS; i++)
        if (scanf("%d", &arr[i]) != 1)
            exit_code = ERROR;
    
    if (scanf("%d", &tmp) != EOF)
        exit_code = ERROR;

    return exit_code;
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