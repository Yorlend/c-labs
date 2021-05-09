#include "my_string.h"
#include <string.h>
#include <stdio.h>

#define DELIMS " ,;:-.!?"

int my_strlen(const char *str)
{
    int len = 0;
    for (const char *c = str; *c != '\0'; c++)
        len++;
    return len;
}

int delete_newline(char *str)
{
    for (char *c = str; *c != '\0'; c++)
        if (*c == '\n')
        {
            *c = '\0';
            return 0;
        }

    return 1;
}

char *my_strtok(char *str, const char *delimiters)
{ 
    static char *position = NULL;
    int i = 0;
    int len = my_strlen(delimiters);
 
    if (!str && !position)
        return NULL;

    if (str && !position)
        position = str;

    char *p_start = position;
    while (1)
    {
        for (i = 0; i < len; i++)
        {
            if (*p_start == delimiters[i])
            {
                p_start++;
                break;
            }
        }
 
        if (i == len) 
        {
            position = p_start;
            break;
        }
    }

    if (*position == '\0')
    {
        position = NULL;
        return position;
    }
 
    while (*position != '\0')
    {
        for (i = 0; i < len; i++)
        {
            if (*position == delimiters[i])
            {
                *position = '\0';
                break;
            }
        }
 
        position++;
        if (i < len)
            break;
    }
 
    return p_start;
}

int check_entries(const char *str1, const char *str2)
{
    int len_words1 = 0;
    int len_words2 = 0;
    int repeat_flag = 0;
    int found = 0;

    char words1[MAX_WORD_LEN][MAX_WORDS_COUNT] = { "0" };
    char words2[MAX_WORD_LEN][MAX_WORDS_COUNT] = { "0" };

    char *mod_str1 = (char *)str1;
    char *mod_str2 = (char *)str2;

    char *word1 = my_strtok(mod_str1, DELIMS);
    while (word1)
    {
        if (my_strlen(word1) > 16)
            return 1;
        strncpy(words1[len_words1], word1, 17);
        word1 = my_strtok(NULL, DELIMS);
        len_words1++;
    }

    if (!len_words1)
        return 1;

    char *word2 = my_strtok(mod_str2, DELIMS);
    while (word2)
    {
        if (my_strlen(word2) > 16)
            return 1;
        strncpy(words2[len_words2], word2, 17);
        word2 = my_strtok(NULL, DELIMS);
        len_words2++;
    }

    if (!len_words2)
        return 1;

    printf("Result: \n");
    for (int i = 0; i < len_words1; i++)
    {
        found = 0;
        for (int k = 0; k < i; k++)
            if (!strcmp(words1[i], words1[k]))
                repeat_flag = 1;

        if (repeat_flag)
        {
            repeat_flag = 0;
            continue;
        }
                
        for (int j = 0; j < len_words2; j++)
            if (!strcmp(words1[i], words2[j]))
            {
                printf("%s yes\n", words1[i]);
                found = 1;
                break;
            }
        if (!found)
            printf("%s no\n", words1[i]);
    }
    return 0;
}

