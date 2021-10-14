#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "status.h"

#define EPS 1e-6

typedef double data_t;

typedef struct
{
    size_t rows;
    size_t cols;
    data_t **data;
} matrix_t;

matrix_t mat_null(void);
void mat_destroy(matrix_t *mat);

bool mat_is_valid(const matrix_t *mat);

status_t mat_read(matrix_t *mat, const char *filename);
status_t mat_readf(matrix_t *mat, FILE *file);

status_t mat_write(const matrix_t *mat, const char *filename);
status_t mat_writef(const matrix_t *mat, FILE *file);

status_t mat_add(matrix_t *res, const matrix_t *left, const matrix_t *right);
status_t mat_mul(matrix_t *res, const matrix_t *left, const matrix_t *right);

status_t mat_gauss_solve(matrix_t *res, const matrix_t *input);

#endif /* __MATRIX_H__ */
