#ifndef DATE_CHECK
#define DATE_CHECK

#include "my_string.h"
#include <stdbool.h>

#define DATE_CORRECT true
#define DATE_WRONG false

typedef struct
{
    int day;
    int month;
    int year;
} date_t;


bool is_leap_year(int year);
bool check_date(date_t date);
bool parse_date(date_t *date, char **str);
int convert_month(char *str_month);

#endif