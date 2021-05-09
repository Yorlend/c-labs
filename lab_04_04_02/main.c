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
        int flag = 0;
        date_t date = { 0, 0, 0 };
        for (char *c = str; *c != '\0'; c++)
        {
            char *pstr = c;
            if (parse_date_raw(&date, &pstr))
            {
                if (!check_date(date))
                    c = pstr - 1;
                else
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (!flag)
            printf("NO\n");
        else
            printf("YES\n");
    }

    return exit_code;
}