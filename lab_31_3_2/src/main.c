#include <stdio.h>
#include "matrix.h"
#include "errors.h"

// вызов программы: ./app.exe <входной файл>
int main(int argc, char* argv[])
{
    int status = SUCCESS;
    matrix_t mat = mat_null();

    if (argc != 2)
        status = BAD_ARGC;

    if (status == SUCCESS)
        status = mat_read(&mat, argv[1]);

    if (status == SUCCESS)
        status = mat_operate(&mat);

    if (status == SUCCESS)
        status = mat_writef(stdout, &mat);
    else if (status == NO_EVEN_NUMS)
        printf("no even nums\n");
    else if (status == BAD_MATRIX)
        printf("incorrect matrix\n");

    mat_free(&mat);
    return status;
}
