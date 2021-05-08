#ifndef MY_STRING
#define MY_STRING
#define MAX_STR_LEN 257
#define MAX_WORD_LEN 17
#define MAX_WORDS_COUNT 128

char *my_strtok(char *str, const char *delim);
int check_entries(const char *str1, const char *str2);
int delete_newline(char *str);
int my_strlen(const char *str);

#endif
