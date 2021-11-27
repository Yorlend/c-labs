#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>

typedef int data_t;

typedef struct matrix
{
    int rows;
    int cols;
    data_t **data;
} matrix_t;


matrix_t mat_null(void);
void mat_free(matrix_t* mat);

bool mat_is_null(const matrix_t* mat);

matrix_t mat_zero(int rows, int cols);

int mat_readf(FILE* file, matrix_t* mat);
int mat_read(matrix_t* mat, const char* filename);

int mat_writef(FILE* file, matrix_t* mat);

// Решает задачу сортировки необходимых элементов в массиве
int mat_operate(matrix_t* mat);

#endif /* __MATRIX_H__ */
