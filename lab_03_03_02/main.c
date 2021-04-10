#include <stdio.h>

#define M 10
#define N 10
#define SUCCESS 0
#define INPUT_ERROR 1

int input_mx(int (*mx)[N], int *row, int *col);
void print_mx(int (*mx)[N], int row, int col);
void form_array(int (*mx)[N], int row, int col, int *arr);
void mx_selection_sort(int (*mx)[N], int row, int col, int *arr);


int main(void)
{
    int exit_code = SUCCESS, col = 0, row = 0;
    int arr[N] = { 0 }, mx[M][N] = { { 0 } };

    exit_code = input_mx(mx, &row, &col);

    if (!exit_code)
    {
        form_array(mx, row, col, arr);
        mx_selection_sort(mx, row, col, arr);
        print_mx(mx, row, col);
    }

    return exit_code;
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

void print_mx(int (*mx)[N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%d ", mx[i][j]);
        printf("\n");
    }
            
}

void form_array(int (*mx)[N], int row, int col, int *arr)
{
    int tmp = 1;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            tmp *= mx[i][j];
        arr[i] = tmp;
        tmp = 1;
    }
}

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

void mx_selection_sort(int (*mx)[N], int row, int col, int *arr)
{
    int min = 0;
    for (int i = 0; i < row - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < row; j++)
            if (arr[j] < arr[min])
                min = j;
        
        swap(&arr[min], &arr[i]);
        for (int j = 0; j < col; j++)
            swap(&mx[min][j], &mx[i][j]);
    }
}