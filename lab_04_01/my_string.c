#include "my_string.h"
#include <stddef.h>

int my_strlen(const char *str)
{
    int len = 0;
    for (const char *c = str; *c != '\0'; c++)
        len++;
    return len;
}

char *my_strpbrk(const char *str1, const char *str2)
{
    for (const char *curr_char_1 = str1; *curr_char_1 != '\0'; curr_char_1++)
        for (const char *curr_char_2 = str2; *curr_char_2 != '\0'; curr_char_2++)
            if (*curr_char_1 == *curr_char_2)
                return (char*)curr_char_1;

    return NULL;
}

char *my_strrchr(const char *str, int c)
{
    int str_length = my_strlen(str);
    for (int i = str_length - 1; i >= 0; i--)
        if (str[i] == c)
            return (char*)(str + i);
        
    return NULL;
}