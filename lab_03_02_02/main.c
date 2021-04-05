#include <stdio.h>

#define M 10
#define N 10
#define SUCCESS 0
#define INPUT_ERROR 1

void print_row(int (*mx)[N], int row, int col);
int input_mx(int (*mx)[N], int *row, int *col);
int digit_sum(int num);
int analyze_row(int (*mx)[N], int row, int col);
void print_minus_row(int col);
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

void print_mx(int (*mx)[N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (analyze_row(mx, i, col))
            print_minus_row(col);
        print_row(mx, i, col);
    }
}

void print_minus_row(int col)
{
    for (int i = 0; i < col; i++)
        printf("-1 ");
    printf("\n");
}

int analyze_row(int (*mx)[N], int row, int col)
{
    int count = 0;
    for (int i = 0; i < col; i++)
        if (digit_sum(mx[row][i]) % 2 != 0)
            count++;
    
    return count > 1;
}

int digit_sum(int num)
{
    int result = 0;
    while (num > 0)
    {
        result += num % 10;
        num /= 10;
    }

    return result;
}

void print_row(int (*mx)[N], int row, int col)
{
    for (int i = 0; i < col; i++)
        printf("%d ", mx[row][i]);
    printf("\n");
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