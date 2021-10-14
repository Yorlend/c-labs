#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

matrix_t mat_null(void)
{
    matrix_t res;

    res.rows = 0;
    res.cols = 0;
    res.data = NULL;

    return res;
}

static void s_free_data(data_t **data, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(data[i]);

    free(data);
}

void mat_destroy(matrix_t *mat)
{
    s_free_data(mat->data, mat->rows);
    *mat = mat_null();
}

bool mat_is_valid(const matrix_t *mat)
{
    return mat != NULL && mat->rows > 0 && mat->cols > 0 && mat->data != NULL;
}

status_t mat_read(matrix_t *mat, const char *filename)
{
    status_t status = bad_file;

    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        status = mat_readf(mat, file);
        fclose(file);
    }

    return status;
}

static data_t **s_allocate_mat_data(size_t rows, size_t cols)
{
    if (rows == 0 || cols == 0)
        return NULL;

    data_t **data = calloc(rows, sizeof(data_t *));

    if (!data)
        return NULL;

    for (size_t i = 0; i < rows; i++)
    {
        data[i] = malloc(cols * sizeof(data_t));
        if (!data[i])
        {
            s_free_data(data, i);
            return NULL;
        }
    }

    return data;
}

static matrix_t s_allocate_mat(size_t rows, size_t cols)
{
    matrix_t res = mat_null();

    res.data = s_allocate_mat_data(rows, cols);
    if (res.data != NULL)
    {
        res.rows = rows;
        res.cols = cols;
    }

    return res;
}

status_t mat_readf(matrix_t *mat, FILE *file)
{
    if (mat == NULL || file == NULL)
        return bad_func_args;

    status_t status = success;
    size_t rows = 0, cols = 0;

    if (fscanf(file, "%lu%lu", &rows, &cols) != 2)
        status = bad_matrix_format;
    else if (rows == 0 || cols == 0)
        status = bad_matrix_dims;
    else
    {
        // allocate space
        *mat = s_allocate_mat(rows, cols);
        if (!mat_is_valid(mat))
            status = memory_error;
    }

    // read values
    for (size_t row = 0; row < rows && status == success; row++)
        for (size_t col = 0; col < cols && status == success; col++)
            if (fscanf(file, "%lf", &mat->data[row][col]) != 1)
                status = bad_matrix_format;

    if (status != success)
        mat_destroy(mat);

    return status;
}

status_t mat_write(const matrix_t *mat, const char *filename)
{
    status_t status = bad_file;

    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        status = mat_writef(mat, file);
        fclose(file);
    }

    return status;
}

status_t mat_writef(const matrix_t *mat, FILE *file)
{
    if (!mat_is_valid(mat) || file == NULL)
        return bad_func_args;

    status_t status = success;

    if (fprintf(file, "%lu %lu\n", mat->rows, mat->cols) < 0)
        status = bad_file;

    for (size_t row = 0; row < mat->rows && status == success; row++)
    {
        for (size_t col = 0; col < mat->cols && status == success; col++)
            if (fprintf(file, col > 0 ? " %lf" : "%lf", mat->data[row][col]) < 0)
                status = bad_file;
        if (fprintf(file, "\n") < 0)
            status = bad_file;
    }

    return status;
}

status_t mat_add(matrix_t *res, const matrix_t *left, const matrix_t *right)
{
    if (res == NULL || !mat_is_valid(left) || !mat_is_valid(right))
        return bad_func_args;

    if (left->rows != right->rows || left->cols != right->cols)
        return bad_matrix_dims;

    *res = s_allocate_mat(left->rows, left->cols);
    if (!mat_is_valid(res))
        return memory_error;

    for (size_t row = 0; row < res->rows; row++)
        for (size_t col = 0; col < res->cols; col++)
            res->data[row][col] = left->data[row][col] + right->data[row][col];

    return success;
}

status_t mat_mul(matrix_t *res, const matrix_t *left, const matrix_t *right)
{
    if (res == NULL || !mat_is_valid(left) || !mat_is_valid(right))
        return bad_func_args;

    if (left->cols != right->rows)
        return bad_matrix_dims;

    *res = s_allocate_mat(left->rows, right->cols);
    if (!mat_is_valid(res))
        return memory_error;

    for (size_t row = 0; row < res->rows; row++)
    {
        for (size_t col = 0; col < res->cols; col++)
        {
            data_t buf = 0;
            for (size_t k = 0; k < left->cols; k++)
                buf += left->data[row][k] * right->data[k][col];
            res->data[row][col] = buf;
        }
    }

    return success;
}

static void s_row_add(matrix_t *mat, size_t dst_index, size_t src_index, data_t factor)
{
    if (mat_is_valid(mat) && src_index < mat->rows && dst_index < mat->rows)
        for (size_t col = 0; col < mat->cols; col++)
            mat->data[dst_index][col] += factor * mat->data[src_index][col];
}

static void s_row_mul(matrix_t *mat, size_t row, data_t factor)
{
    for (size_t col = 0; col < mat->cols; col++)
        mat->data[row][col] *= factor;
}

// finds max in given row except last element
static size_t s_find_max_in_row(const matrix_t *mat, size_t row)
{
    data_t max = mat->data[row][0];
    size_t index = 0;

    for (size_t col = 1; col + 1 < mat->cols; col++)
    {
        if (fabs(mat->data[row][col]) > fabs(max))
        {
            max = fabs(mat->data[row][col]);
            index = col;
        }
    }

    return index;
}

static matrix_t s_mat_clone(const matrix_t *src)
{
    matrix_t res = s_allocate_mat(src->rows, src->cols);

    if (mat_is_valid(&res))
        for (size_t row = 0; row < res.rows; row++)
            memcpy(res.data[row], src->data[row], res.cols * sizeof(data_t));

    return res;
}

static void s_swap_cols(matrix_t *mat, size_t col_1, size_t col_2)
{
    for (size_t row = 0; row < mat->rows; row++)
    {
        data_t tmp = mat->data[row][col_1];
        mat->data[row][col_1] = mat->data[row][col_2];
        mat->data[row][col_2] = tmp;
    }
}

static status_t s_solve_gauss(matrix_t *res, matrix_t *input, size_t *col_indices)
{
    for (size_t row = 0; row < input->rows; row++)
    {
        size_t max_col = s_find_max_in_row(input, row);
        if (row != max_col)
        {
            s_swap_cols(input, row, max_col);
            size_t tmp = col_indices[row];
            col_indices[row] = col_indices[max_col];
            col_indices[max_col] = tmp;
        }

        data_t max_el = input->data[row][row];
        if (fabs(max_el) < EPS)
            return solve_error;

        for (size_t rtmp = 0; rtmp < input->rows; rtmp++)
        {
            if (rtmp != row)
            {
                data_t factor = -input->data[rtmp][row] / max_el;
                s_row_add(input, rtmp, row, factor);
            }
        }

        s_row_mul(input, row, 1 / max_el);
    }

    for (size_t row = 0; row < input->rows; row++)
        res->data[row][0] = input->data[col_indices[row]][input->cols - 1];

    return success;
}

static size_t *s_allocate_col_indices(size_t cols)
{
    size_t *data = malloc(cols * sizeof(size_t));

    if (data != NULL)
        for (size_t col = 0; col < cols; col++)
            data[col] = col;

    return data;
}

status_t mat_gauss_solve(matrix_t *res, const matrix_t *input)
{
    if (!mat_is_valid(input) || res == NULL)
        return bad_func_args;

    if (input->rows + 1 != input->cols)
        return bad_matrix_dims;

    // column indices
    size_t *col_indices = s_allocate_col_indices(input->cols - 1);
    if (col_indices == NULL)
        return memory_error;

    status_t status = memory_error;

    *res = s_allocate_mat(input->rows, 1);
    if (mat_is_valid(res))
    {
        matrix_t input_copy = s_mat_clone(input);

        if (mat_is_valid(&input_copy))
        {
            status = s_solve_gauss(res, &input_copy, col_indices);
            mat_destroy(&input_copy);
        }

        if (status != success)
            mat_destroy(res);
    }

    free(col_indices);
    return status;
}
