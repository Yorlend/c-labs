#include <stdio.h>

#define N 10

int input_array(int *arr, int size);
double average_neg(int *arr, int size);

int main(void)
{
    int arr[N] = { 0 }, size;
    double result = 0.;

    scanf("%d", &size);
    if (size > N || size < 1)
        return 1;

    if (input_array(arr, size) == 1)
        return 1;
    
    result = average_neg(arr, size);

    if (result == 0)
        return 1;

    printf("%lf", result);

    return 0;
}

int input_array(int *arr, int size)
{
    int tmp;
    for (int i = 0; i < size; i++)
        if (scanf("%d", &arr[i]) != 1)
            return 1;

    if (scanf("%d", &tmp) != EOF)
        return 1;

    return 0;
}

double average_neg(int *arr, int size)
{
    double res = 0.;
    int n = 0, sum = 0;

    for (int i = 0; i < size; i++)
        if (arr[i] < 0)
        {
            n++;
            sum += arr[i];
        }
    if (n)
        res = (double)sum / n;

    return res;
}
