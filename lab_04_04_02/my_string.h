#ifndef MY_STRING
#define MY_STRING
#define MAX_STR_LEN 257
#define MAX_WORD_LEN 17
#define MAX_WORDS_COUNT 128
#define SUCCESS 0
#define ERROR 1
#define DELIMS " ,;:-.!?"

#include <stdbool.h>

int input_string(char *str);
int split_str(char (*str_array)[MAX_WORD_LEN], int *size, char *str);

/**
 * str = "13bcd"
 * parse_uint(..., &str) == true
 * str == "bcd"
 * 
 * str = "abcd"
 * parse_uint(..., &str) == false
 * str == "abcd"
 */
bool parse_uint(int *value, char **str);
bool parse_char(char **str, char chr);
bool parse_word(char *word, char **str);
bool parse_wspace(char **str);
bool parse_wspace_p(char **str);
bool parse_wspace_s(char **str);

#endif