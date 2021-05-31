#include "file_process.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int find_avg(FILE *file, double *avg)
{
    if (file == NULL || avg == NULL)
        return EXIT_FAILURE;
    
    fseek(file, 0, SEEK_SET);

    double sum = 0.0;
    int count = 0;

    double num;
    while (fscanf(file, "%lf", &num) > 0)
    {
        sum += num;
        count++;
    }

    *avg = sum / count;

    return EXIT_SUCCESS;
}

int close_to_avg(FILE *file, double *res, double avg)
{
    if (file == NULL || res == NULL)
        return EXIT_FAILURE;

    fseek(file, 0, SEEK_SET);

    double num;
    if (fscanf(file, "%lf", &num) <= 0)
        return EXIT_FAILURE;

    double eps = fabs(num - avg);
    *res = num;

    int rc;
    while ((rc = fscanf(file, "%lf", &num)) > 0)
    {
        double tmp = fabs(num - avg);
        if (tmp < eps)
        {
            eps = tmp;
            *res = num;
        }
    }
    if (rc != EOF)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int process(FILE *file, double *res)
{
    int exit_code = EXIT_SUCCESS;
    double avg = 0.0;

    exit_code = find_avg(file, &avg);

    if (!exit_code)
        exit_code = close_to_avg(file, res, avg);

    return exit_code;
}
