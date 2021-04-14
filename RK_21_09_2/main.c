#include <stdio.h>

#define N 10
#define SUCCESS 0
#define INPUT_ERROR -1
#define NO_POSITIVE -2

int input_array(int *arr, int *size);
void output_array(int *arr, int size);
int pos_sum(int *arr, int size);
void replace_negative(int *arr, int size, int sum, int pos);

int main(void)
{
    int exit_code = SUCCESS, arr[N] = { 0 }, result = 0;
    int size = 0;

    if (input_array(arr, &size) == INPUT_ERROR)
        exit_code = INPUT_ERROR;
    else
    {
        result = pos_sum(arr, size);
        if (result == NO_POSITIVE)
            exit_code = NO_POSITIVE;
    }

    if (exit_code == SUCCESS)
    {
        replace_negative(arr, size, result, result % 2);

        output_array(arr, size);
    }

    return exit_code;
}

void replace_negative(int *arr, int size, int sum, int pos)
{
    if (pos == 0)
        for (int i = 0; i < size; i++)
            if (arr[i] < 0)
            {
                arr[i] = sum;
                break;
            }
    if (pos == 1)
        for (int i = size - 1; i >= 0; i--)
            if (arr[i] < 0)
            {
                arr[i] = sum;
                break;
            }
}

int input_array(int *arr, int *size)
{
    int exit_code = SUCCESS;
    scanf("%d", size);
    if (*size > N || * size < 1)
        exit_code = INPUT_ERROR;
    for (int i = 0; i < *size && exit_code == SUCCESS; i++)
        if (scanf("%d", &arr[i]) != 1)
            exit_code = INPUT_ERROR;

    return exit_code;
}

void output_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d\n", arr[i]);   
}

int pos_sum(int *arr, int size)
{
    int res = 0, negative = 1;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0)
            res += arr[i];
        if (arr[i] < 0)
            negative = 0;
    }
    
    if (res == 0 || negative)
        return NO_POSITIVE;
    return res;
}