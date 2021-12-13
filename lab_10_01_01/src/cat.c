#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "cat.h"
#include "file_utils.h"


cat_t null_cat(void)
{
    cat_t res;
    res.name = NULL;
    reset_date(&res.date);
    return res;
}

void free_cat(cat_t *cat)
{
    if (cat->name != NULL)
        free(cat->name);
    *cat = null_cat();
}

cat_t *move_cat(cat_t *cat)
{
    cat_t *moved = malloc(sizeof(cat_t));
    if (moved != NULL)
        *moved = *cat;

    return moved;
}

int input_cat(FILE *file, cat_t *cat)
{
    int status = input_string(file, &cat->name);

    if (status == EXIT_SUCCESS)
        status = input_date(file, &cat->date);

    if (status != EXIT_SUCCESS)
        free_cat(cat);

    return status;
}

int prompt_cat(cat_t *cat)
{
    printf("Введите имя пациента: ");
    int status = input_string(stdin, &cat->name);

    if (status == EXIT_SUCCESS)
    {
        printf("Введите дату поступления (ДД.ММ.ГГГГ): ");
        status = input_date(stdin, &cat->date);
    }

    if (status != EXIT_SUCCESS)
        free_cat(cat);

    return status;
}

void output_cat(FILE *file, const void *cat)
{
    if (((const cat_t*)cat)->name == NULL)
        fprintf(file, "(null)\n");
    else
    {
        char *str = date_to_str(&((const cat_t*)cat)->date);
        fprintf(file, "%s\n%s\n", ((const cat_t*)cat)->name, str);
    }
}

int date_compare(const void *cat1, const void *cat2)
{
    const cat_t *c1 = (const cat_t*)cat1;
    const cat_t *c2 = (const cat_t*)cat2;
    int d_year = c1->date.year - c2->date.year;
    int d_month = c1->date.month - c2->date.month;
    int d_day = c1->date.day - c2->date.day;

    if (d_year == 0)
    {
        if (d_month == 0)
            return d_day;
        return d_month;
    }

    return d_year;
}
