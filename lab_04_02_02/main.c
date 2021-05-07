#include <stdio.h>
#include "my_string.h"

#define SUCCESS 0
#define ERROR 1

int main(void)
{
    int exit_code = SUCCESS;
    char str1[MAX_STR_LEN];
    char str2[MAX_STR_LEN];

    if (fgets(str1, MAX_STR_LEN, stdin) == NULL ||\
    fgets(str2, MAX_STR_LEN, stdin) == NULL)
        exit_code = ERROR;

    if (!exit_code)
        exit_code = delete_newline(str1) || delete_newline(str2);
    
    if (!exit_code)
        exit_code = check_entries(str1, str2);

    return exit_code;
}
