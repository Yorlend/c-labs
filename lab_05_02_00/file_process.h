#ifndef _FILE_PROCESS_H
#define _FILE_PROCESS_H

#include <stdio.h>


int find_avg(FILE *file, double *avg);
int close_to_avg(FILE *file, double *res, double avg);
int process(FILE *file, double *res);

#endif