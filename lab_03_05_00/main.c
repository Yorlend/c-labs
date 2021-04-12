#include <stdio.h>
#include <math.h>

#define M 10
#define N 10
#define SUCCESS 0
#define INPUT_ERROR 1

int is_prime(int num);
int input_mx(int (*mx)[N], int *row, int *col);
int form_array(int (*mx)[N], int row, int col, int *arr);
void swap(int *first, int *second);
void reverse_array(int *arr, int size);
void print_mx(int (*mx)[N], int row, int col);
void insert_primes(int (*mx)[N], int row, int col, int *arr);

int main(void)
{
    int exit_code = SUCCESS, col = 0, row = 0, size = 0;
    int arr[N * N] = { 0 }, mx[M][N] = { { 0 } };

    exit_code = input_mx(mx, &row, &col);

    if (!exit_code)
        size = form_array(mx, row, col, arr);
    
    if (size == 0)
        exit_code = INPUT_ERROR;
    
    if (!exit_code)
    {
        reverse_array(arr, size);
        insert_primes(mx, row, col, arr);
        print_mx(mx, row, col);
    }


    return exit_code;
}

void print_mx(int (*mx)[N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%d ", mx[i][j]);
        printf("\n");
    }
}

void insert_primes(int (*mx)[N], int row, int col, int *arr)
{
    int k = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (is_prime(mx[i][j]))
            {
                mx[i][j] = arr[k];
                k++;
            }
}

void reverse_array(int *arr, int size)
{
    for (int i = 0; i < size / 2; i++)
        swap(&arr[i], &arr[size - i - 1]);
}

int form_array(int (*mx)[N], int row, int col, int *arr)
{
    int size = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (is_prime(mx[i][j]))
            {
                arr[size] = mx[i][j];
                size++;
            }
    return size;
}

int input_mx(int (*mx)[N], int *row, int *col)
{
    printf("Input matrix size M x N:\n");
    if (scanf("%d%d", row, col) != 2 || *row < 1 || *col < 1 || *row * *col > N * M)
        return INPUT_ERROR;
    
    printf("Input elements of the matrix:\n");
    for (int i = 0; i < *row; i++)
        for (int j = 0; j < *col; j++)
            if (scanf("%d", &mx[i][j]) != 1)
                return INPUT_ERROR;

    return SUCCESS;
}

int is_prime(int num)
{
    if (num < 2)
        return 0;
    if (num == 2)
        return 1;
    for (int i = 2; i < sqrt(num) + 1; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}