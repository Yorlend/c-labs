#include <stdio.h>
#include "my_string.h"



int main(void)
{
    int exit_code = SUCCESS;

    int size = 0;
    char str[MAX_STR_LEN] = "";
    char words[MAX_WORDS_COUNT][MAX_WORD_LEN] = { "0" };

    exit_code = input_string(str);
    
    if (!exit_code)
        exit_code = split_str(words, &size, str);
    
    if (!exit_code)
    {
        reverse_array(words, size);
        exit_code = remove_occurence(words, &size);
    }

    if (!exit_code)
    {
        join(str, words, size);
        printf("Result: %s\n", str);
    }

    return exit_code;
}