#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define ERROR 1
#define SUCCESS 0
#define EPS 1e-5

int input_array(int *arr, int *size);
void output_array(int *arr, int size);
int reform_array(int *arr, int *size);
int is_perfect_square(int num);

int main(void)
{
    int exit_code = SUCCESS;
    int arr[N] = { 0 }, result_arr[N], size;
    if (input_array(arr, &size) == ERROR)
        exit_code = ERROR;
    else
        exit_code = reform_array(arr, &size);

    if (exit_code == SUCCESS)
        output_array(result_arr, size);
    
    return exit_code;
}

int input_array(int *arr, int *size)
{
    int tmp, exit_code = SUCCESS;
    scanf("%d", size);
    if (*size > N)
        exit_code = ERROR;
    for (int i = 0; i < *size && exit_code == SUCCESS; i++)
        if (scanf("%d", &arr[i]) != 1)
            exit_code = ERROR;
    
    if (scanf("%d", &tmp) != EOF)
        exit_code = ERROR;

    return exit_code;
}

void output_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d\n", arr[i]);   
}

int reform_array(int *arr, int *size)
{
    int i = 0;
    while (i < *size)
    {
        if (is_perfect_square(arr[i]))
        {
            for (int tmp = i; tmp < *size - 1; tmp++)
                arr[tmp] = arr[tmp + 1];
            (*size)--;
            continue;
        }

        i++;
    }

    return *size == 0;
}

int is_perfect_square(int num)
{
    int result = 0;
    for (int i = 1; i < sqrt(num) + 1; i++)
        if (i*i == num)
            result = 1;
    
    return result;
}