#ifndef _PRODUCT_H
#define	_PRODUCT_H

#include <stdint.h>
#include <stdio.h>
#include "constants.h"


typedef struct 
{
    char name[MAX_STR_LEN];
    char manufacturer[MAX_MAN_LEN];
    uint32_t price;
    uint32_t quantity;
} product_t;

int sort_file(FILE *fsrc, FILE *fdest);
int add_unit(char *filename, product_t *unit);

#endif
