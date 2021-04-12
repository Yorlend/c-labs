#include <stdio.h>

#define SUCCESS 0
#define INPUT_ERROR 1
#define M 10
#define N 10

int input_mx(int (*mx)[N], int *row, int *col);
void print_mx(int (*mx)[N], int row, int col);

int main(void)
{
    int exit_code = SUCCESS, col = 0, row = 0;
    int mx[M][N] = { { 0 } };

    exit_code = input_mx(mx, &row, &col);

    if (!exit_code)
        print_mx(mx, row, col);

    return exit_code;
}

int input_mx(int (*mx)[N], int *row, int *col)
{
    printf("Input matrix size M x N:\n");
    if (scanf("%d%d", row, col) != 2 || *row < 1 || *col < 1 || *row > M || *col > N)
        return INPUT_ERROR;

    mx[0][0] = *row * *col - *row + 1;
    for (int i = 1; i < *row; i++)
        mx[i][0] = mx[i - 1][0] + 1;
    for (int i = 0; i < *row; i++)
        for (int j = 1; j < *col; j++)
            mx[i][j] = mx[i][j - 1] - 1 - 2 * (i * (j % 2) +
                (*row - 1 - i) * ((j + 1) % 2));

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