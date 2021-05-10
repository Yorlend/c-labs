#include <string.h>
#include "my_string.h"
#include <stdio.h>
#include <ctype.h>

#define ALPHA_LOWER "abcdefghijklmnopqrstuvwxyz"
#define ALPHA_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALPHA_CHARS ALPHA_LOWER ALPHA_UPPER

int input_string(char *str)
{
    if (fgets(str, MAX_STR_LEN, stdin) == NULL)
        return ERROR;

    for (char *c = str; *c != '\0'; c++)
        if (*c == '\n')
        {
            *c = '\0';
            return SUCCESS;
        }

    return ERROR;
}

int split_str(char (*str_array)[MAX_WORD_LEN], int *size, char *str)
{
    char *word = strtok(str, DELIMS);
    while (word)
    {
        if (strlen(word) > 16)
            return ERROR;
        strncpy(str_array[*size], word, MAX_WORD_LEN);
        (*size)++;
        word = strtok(NULL, DELIMS);
    }

    return SUCCESS;
}

bool parse_uint(int *value, char **str)
{
    if (!isdigit(**str))
        return false;

    *value = 0;
    while (isdigit(**str))
        *value = 10 * *value + *((*str)++) - '0';

    return true;
}

bool parse_char(char **str, char chr)
{
    if (**str == chr)
    {
        (*str)++;
        return true;
    }

    return false;
}

bool parse_word(char *word, char **str)
{
    if (!isalpha(**str))
        return false;
    
    size_t word_size = strspn(*str, ALPHA_CHARS);
    if (word_size >= MAX_WORD_LEN - 1)
        return false;

    strncpy(word, *str, word_size);
    word[word_size] = '\0';
    *str += word_size;

    return true;
}

bool parse_space(char **str)
{
    if (!parse_char(str, ' '))
        return false;
    while (parse_char(str, ' '));

    return true;
}

bool parse_space_mb(char **str)
{
    while (parse_char(str, ' ') || parse_char(str, '\t'));

    return true;
}
