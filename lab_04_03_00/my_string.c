#include <string.h>
#include "my_string.h"
#include <stdio.h>

static void swap(char *a, char *b)
{
    char tmp[MAX_WORD_LEN];
    strncpy(tmp, a, MAX_WORD_LEN);
    strncpy(a, b, MAX_WORD_LEN);
    strncpy(b, tmp, MAX_WORD_LEN);
}

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

int remove_char(char *str, int index)
{
    if (str == NULL)
        return ERROR;

    int str_len = strlen(str);
    if (index < 0 || index >= str_len)
        return ERROR;

    for (int i = index; i < str_len; i++)
        str[i] = str[i + 1];

    return SUCCESS;
}

int remove_first(char *str)
{
    if (str == NULL)
        return ERROR;

    int str_len = strlen(str);
    
    if (str_len < 1)
        return ERROR;

    char first = str[0];

    for (int i = 1; i < str_len; i++)
        if (str[i] == first)
            remove_char(str, i--);

    return SUCCESS;
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

void reverse_array(char (*str_array)[MAX_WORD_LEN], int size)
{
    for (int i = 0, j = size - 1; i < j; i++, j--)
        swap(str_array[i], str_array[j]);
}


void remove_word(char (*str_array)[MAX_WORD_LEN], int *size, int index)
{
    for (int i = index; i < *size; i++)
        strncpy(str_array[i], str_array[i + 1], MAX_WORD_LEN);
    (*size)--;
}

int remove_occurence(char (*str_array)[MAX_WORD_LEN], int *size)
{
    char first[MAX_WORD_LEN];
    strncpy(first, str_array[0], MAX_WORD_LEN);
    for (int i = 0; i < *size; i++)
        if (!strncmp(str_array[i], first, MAX_WORD_LEN))
            remove_word(str_array, size, i--);
    
    if (!(*size))
        return ERROR;
    return SUCCESS;
}

void join(char *str, char (*str_array)[MAX_WORD_LEN], int size)
{
    *str = '\0';
    for (int i = 0; i < size; i++)
    {
        if (i > 0)
            strcat(str, " ");
        strncat(str, str_array[i], MAX_WORD_LEN);
    }
}