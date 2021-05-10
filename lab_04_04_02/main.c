#include <stdio.h>
#include <string.h>
#include "my_string.h"
#include "date_check.h"

int main(void)
{
    int exit_code = SUCCESS;
    char str[MAX_STR_LEN] = "";
    char split_s[MAX_STR_LEN] = "";    

    char words[MAX_WORDS_COUNT][MAX_WORD_LEN];
    int size = 0;

    exit_code = input_string(str);

    strncpy(split_s, str, MAX_STR_LEN);

    if (!exit_code)
        exit_code = split_str(words, &size, split_s);

    if (!exit_code)
    {
        date_t date = { 0, 0, 0 };
        char *pstr = str;
        if (parse_space_mb(&pstr) && parse_date_raw(&date, &pstr) \
            && check_date(date) && parse_space_mb(&pstr))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return exit_code;
}