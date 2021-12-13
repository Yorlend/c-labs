#ifndef __DATE_H__
#define __DATE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
} date_t;

/**
 * @brief Check if date is leap
 * 
 * @param year 
 * @return true 
 * @return false 
 */
bool is_leap_year(uint16_t year);

/**
 * @brief resets current date
 * 
 * @param date 
 */
void reset_date(date_t *date);

/**
 * @brief Checks if date is valid
 * 
 * @param date 
 * @return true 
 * @return false 
 */
bool date_valid(const date_t *date);

/**
 * @brief Transforms string to date
 * 
 * @param str 
 * @return date_t 
 */
date_t str_to_date(const char *str);

/**
 * @brief Transforms date to string
 * 
 * @param date 
 * @return char* 
 */
char *date_to_str(const date_t *date);

/**
 * @brief Inputs date from file
 * 
 * @param file 
 * @param date 
 * @return int 
 */
int input_date(FILE *file, date_t *date);

#endif /* __DATE_H__ */
