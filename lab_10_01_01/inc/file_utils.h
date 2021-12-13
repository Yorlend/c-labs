#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Checks if file is empty
 * 
 * @param file 
 * @return true 
 * @return false 
 */
bool file_is_empty(FILE *file);

/**
 * @brief Inputs string from file
 * 
 * @param file 
 * @param str 
 * @return int 
 */
int input_string(FILE *file, char **str);

/**
 * @brief Inputs integer from file
 * 
 * @param file 
 * @param num 
 * @return int 
 */
int input_int(FILE *file, int *num);


#endif /* __FILE_UTILS_H__ */
