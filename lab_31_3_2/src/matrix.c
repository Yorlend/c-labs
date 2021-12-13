#include <stdlib.h>
#include "matrix.h"
#include "errors.h"

matrix_t mat_null(void)
{
    return (matrix_t){ .cols = 0, .rows = 0, .data = NULL };
}

void mat_free(matrix_t* mat)
{
    if (mat->data != NULL)
    {
        for (int row = 0; row < mat->rows; row++)
            free(mat->data[row]);
        free(mat->data);
    }

    *mat = mat_null();
}

bool mat_is_null(const matrix_t* mat)
{
    return mat->rows == 0 || mat->cols == 0 || mat->data == NULL;
}

static data_t **allocate_mat_d(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
        return NULL;        

    data_t **data = calloc((size_t)rows, sizeof(data_t *));
    if (data == NULL)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        data[i] = malloc((size_t)cols * sizeof(data_t));
        if (data[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(data[i]);
            free(data);
            break;
        }
    }

    return data;
}

static matrix_t allocate_mat(int rows, int cols)
{    
    matrix_t mat = mat_null();
    mat.data = allocate_mat_d(rows, cols);
    if (mat.data != NULL)
    {
        mat.rows = rows;
        mat.cols = cols;
    }

    return mat;
}

int mat_readf(FILE* file, matrix_t* mat)
{
    *mat = mat_null();
    int status = SUCCESS;

    int rows = 0, cols = 0;
    if (fscanf(file, "%d%d", &rows, &cols) != 2)
        status = BAD_MATRIX;
        
    if (status == SUCCESS)
        *mat = allocate_mat(rows, cols);
    
    if (status == SUCCESS)
        if (mat_is_null(mat))
            status = MEM_ERR;

    if (status == SUCCESS)
    {
        for (int i = 0; i < rows && status == SUCCESS; i++)
            for (int j = 0; j < cols && status == SUCCESS; j++)
                if (fscanf(file, "%d", &mat->data[i][j]) != 1)
                    status = BAD_MATRIX;        
    }

    if (status != SUCCESS)
        mat_free(mat);

    return status;
}

int mat_read(matrix_t* mat, const char* filename)
{
    int status = BAD_FILENAME;

    FILE* file = fopen(filename, "r");
    if (file)
    {
        status = mat_readf(file, mat);
        fclose(file);
    }

    return status;
}

int mat_writef(FILE* file, matrix_t* mat)
{
    for (int row = 0; row < mat->rows; row++)
    {
        for (int col = 0; col < mat->cols; col++)
        {
            if (col > 0)
                fprintf(file, " ");
            fprintf(file, "%d", mat->data[row][col]);
        }
        fprintf(file, "\n");
    }

    return SUCCESS;
}

static int sum_digits(data_t number)
{
    number = abs(number);
    int sum = 0;

    while (number != 0)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

static bool sum_is_even(data_t number)
{
    return sum_digits(number) % 2 == 0;
}

// считает число подходящих элементов
static int count_nums(matrix_t* mat)
{
    int count = 0;

    for (int row = 0; row < mat->rows; row++)
        for (int col = 0; col < mat->cols; col++)
            if (sum_is_even(mat->data[row][col]))
                count++;

    return count;
}

static void extract_nums(matrix_t* mat, data_t* buffer)
{
    for (int col = 0; col < mat->cols; col++)
    {
        for (int row = 0; row < mat->rows; row++)
        {
            if (sum_is_even(mat->data[row][col]))
            {
                *buffer = mat->data[row][col];
                buffer++;
            }
        }
    }
}

static void sort_nums(data_t* array, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (sum_digits(array[j]) < sum_digits(array[i]))
            {
                data_t tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

static void insert_nums(matrix_t* mat, data_t* buffer)
{
    for (int col = 0; col < mat->cols; col++)
    {
        for (int row = 0; row < mat->rows; row++)
        {
            if (sum_is_even(mat->data[row][col]))
            {
                mat->data[row][col] = *buffer;
                buffer++;
            }
        }
    }
}

int mat_operate(matrix_t* mat)
{
    int status = SUCCESS;
    int count = 0;
    data_t* buffer = NULL;

    if (mat_is_null(mat))
        status = BAD_MATRIX;

    if (status == SUCCESS)
    {
        count = count_nums(mat);
        if (count == 0)
            status = NO_EVEN_NUMS;
    }

    if (status == SUCCESS)
    {
        buffer = malloc((size_t)count * sizeof(data_t));
        if (buffer == NULL)
            status = MEM_ERR;
    }

    if (status == SUCCESS)
    {
        extract_nums(mat, buffer);
        sort_nums(buffer, count);
        insert_nums(mat, buffer);
        free(buffer);
    }

    return status;
}
