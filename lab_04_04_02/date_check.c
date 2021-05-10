#include "date_check.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool is_leap_year(int year)
{
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

bool check_date(date_t date)
{
    if (date.day < 1 || date.day > 31)
        return DATE_WRONG;
    
    if (date.month < 0 || date.month > 11)
        return DATE_WRONG;

    if (date.year < 1000 || date.year > 9999)
        return DATE_WRONG;

    if (date.month == 1)
    {
        if (is_leap_year(date.year))
        {
            if (date.day > 29)
                return DATE_WRONG;
        }
        else if (date.day > 28)
            return DATE_WRONG;
    }
    
    if ((date.month + (date.month > 6)) % 2 == 1)
        if (date.day > 30)
            return DATE_WRONG;

    return DATE_CORRECT;
}

bool parse_date_raw(date_t *date, char **str)
{
    char *tmp = *str;
    char month[MAX_WORD_LEN];

    date_t res;
    if (!parse_uint(&res.day, &tmp) \
        || !parse_space(&tmp) \
        || !parse_word(month, &tmp) \
        || !parse_space(&tmp) \
        || !parse_uint(&res.year, &tmp))
        return false;
    
    for (size_t i = 0; i < strlen(month); i++)
        month[i] = tolower(month[i]);

    res.month = convert_month(month);
    
    *date = res;
    *str = tmp;
    return true;
}

int convert_month(char *str_month)
{
    const char *monthes[] = {
        "january",
        "february",
        "march",
        "april",
        "may",
        "june",
        "july",
        "august",
        "september",
        "october",
        "november",
        "december"
    };

    int id = -1;
    for (size_t i = 0; i < sizeof(monthes) / sizeof(const char *); i++)
        if (strcmp(str_month, monthes[i]) == 0)
            id = i;
    
    return id;
}
