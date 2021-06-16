#ifndef _FILE_PROCESS_H
#define _FILE_PROCESS_H

#include <stdio.h>

int get_number_by_pos(FILE *file, int *num, size_t pos);
int put_number_by_pos(FILE *file, int num, size_t pos);
int sort_file(FILE *file);

#endif