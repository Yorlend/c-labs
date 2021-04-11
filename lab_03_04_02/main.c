#include <stdio.h>
#include <limits.h>

#define N 10
#define SUCCESS 0
#define ERROR 1

int aux_diag(int mx[][N], int row, int col);
int input_mx(int (*mx)[N], int *row, int *col);

int main(void)
{
    int exit_code = SUCCESS, col = 0, row = 0;
    int res = 0, mx[N][N] = { { 0 } };

    exit_code = input_mx(mx, &row, &col);

    if (!exit_code)
    {
        res = aux_diag(mx, row, col);
        if (res == 1)
            exit_code = ERROR;
        else
            printf("%d\n", res);
    }


    return exit_code;
}

int input_mx(int (*mx)[N], int *row, int *col)
{
    printf("Input matrix size M x N:\n");
    if (scanf("%d%d", row, col) != 2 || *row < 1 || *col < 1 || *row * *col > N * N || *row != *col)
        return ERROR;
    
    printf("Input elements of the matrix:\n");
    for (int i = 0; i < *row; i++)
        for (int j = 0; j < *col; j++)
            if (scanf("%d", &mx[i][j]) != 1)
                return ERROR;

    return SUCCESS;
}

int aux_diag(int mx[][N], int row, int col)
{
    (void) row;
    int top = 0;
    int max = INT_MIN;
    
    for (int i = col - 1; i > -1; i--)
    {
        for (int j = top; j < col; j++)
            if (mx[j][i] % 10 == 5 && mx[j][i] > max)
                max = mx[j][i];
        top++;
    }

    if (max == INT_MIN)
        return ERROR;
    return max;
}
