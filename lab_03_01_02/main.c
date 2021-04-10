#include <stdio.h>

#define M 10
#define N 10
#define SUCCESS 0
#define INPUT_ERROR 1

int input_mx(int (*mx)[N], int *row, int *col);
int check_col(int (*mx)[N], int row, int col_to_check);
void print_arr(int *arr, int size);
void form_array(int *arr, int (*mx)[N], int row, int col);

int main(void)
{
    int exit_code = SUCCESS, col = 0, row = 0;
    int mx[M][N] = { { 0 } };
    int res[N] = { 0 };

    exit_code = input_mx(mx, &row, &col);

    if (!exit_code)
    {
        form_array(res, mx, row, col);
        print_arr(res, col);
    }

    return exit_code;
}

void form_array(int *arr, int (*mx)[N], int row, int col)
{
    for (int i = 0; i < col; i++)
        arr[i] = check_col(mx, row, i);
}

int check_col(int (*mx)[N], int row, int col_to_check)
{
    int res = 0;
    for (int i = 0; i < row - 1; i++)
    {
        res = 1;
        if (mx[i][col_to_check] * mx[i + 1][col_to_check] >= 0)
        {
            res = 0;
            break;
        }
    }
    return res;    
}

int input_mx(int (*mx)[N], int *row, int *col)
{
    int rc = 0;

    printf("Input matrix size M x N:\n");
    if (scanf("%d%d", row, col) != 2 || *row < 1 || *col < 1 || *row * *col > N * M)
        return INPUT_ERROR;

    printf("Input elements of the matrix:\n");
    for (int i = 0; i < *row; i++)
        for (int j = 0; j < *col; j++)
            if (scanf("%d", &mx[i][j]) != 1)
                return INPUT_ERROR;
    
    if (scanf("%d", &rc) != EOF)
        return INPUT_ERROR;

    return SUCCESS;
}

void print_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}