#ifndef MY_STRING
#define MY_STRING
#define MAX_STR_LEN 257
#define MAX_WORD_LEN 17
#define MAX_WORDS_COUNT 128
#define SUCCESS 0
#define ERROR 1
#define DELIMS " ,;:-.!?"

int input_string(char *str);
int remove_first(char *str);
int remove_char(char *str, int index);
int split_str(char (*str_array)[MAX_WORD_LEN], int *size, char *str);
int remove_occurence(char (*str_array)[MAX_WORD_LEN], int *size);
void reverse_array(char (*str_array)[MAX_WORD_LEN], int size);
void join(char *str, char (*str_array)[MAX_WORD_LEN], int size);
void remove_word(char (*str_array)[MAX_WORD_LEN], int *size, int index);

#endif