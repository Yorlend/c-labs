#include "file_IO.h"
#include <stdio.h>

int create_bin(FILE *f, char *filename)
{
    f = fopen(filename, "wb");
    if (f == NULL)
        return FILE_ERROR;

    int size = 0;
    int num = 0;

    #ifdef DETAILED_OUTPUT
    printf("Введите количество элементов в файле:\n");
    #endif
    if (scanf("%d", &size) != 1 || size < 1)
        return INP_ERROR;
    #ifdef DETAILED_OUTPUT
    printf("Введите целые числа для записи в файл:\n");
    #endif
    for (int i = 0; i < size; i++)
    {
        if (scanf("%d", &num) != 1)
            return INP_ERROR;
        if (fwrite(&num, sizeof(int), 1, f) != 1)
            return INP_ERROR;
    }

    fclose(f);

    return SUCCESS;
}

int process_bin(FILE *f, char *filename)
{
    f = fopen(filename, "rb");
    if (f == NULL)
        return FILE_ERROR;
    
    int i = 1, max_index = 0, sum = 0;
    int max, num = 0;
    if (fread(&max, sizeof(int), 1, f) != 1)
        return FILE_ERROR;
    int rc;
    while (1)
    {
        rc = fread(&num, sizeof(int), 1, f);

        if (rc != 1)
            break;

        if (num > max)
        {
            max_index = i;
            max = num;
        }
        i++;
    }
    rewind(f);


    i = 0;
    while (i < max_index)
    {
        fread(&num, sizeof(int), 1, f);
        sum += (int) num;
        i++;
    }
    fclose(f);

    f = fopen(filename, "rb+");
    fseek(f, (int) sizeof(int) * max_index, SEEK_SET);
    fwrite(&sum, sizeof(int), 1, f);

    fclose(f);

    return SUCCESS;
}

int read_bin(FILE *f, char *filename)
{
    f = fopen(filename, "rb");
    if (f == NULL)
        return FILE_ERROR;

    int num = 0;

    while (1)
    {
        if (fread(&num, sizeof(int), 1, f) != 1)
            break;
        printf("%d ", num);
    }
    printf("\n");

    return SUCCESS;
}
