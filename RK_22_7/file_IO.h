#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>

#define SUCCESS 0
#define FILE_ERROR 1
#define INP_ERROR 2

int create_bin(FILE *f, char *filename);
int process_bin(FILE *f, char *filename);
int read_bin(FILE *f, char *filename);

#endif