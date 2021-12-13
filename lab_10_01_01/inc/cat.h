#ifndef __CAT_H__
#define __CAT_H__

#include "date.h"


typedef struct cat
{
    char *name;
    date_t date;
} cat_t;

/**
 * @brief Null constructor
 * 
 * @return cat_t 
 */
cat_t null_cat(void);

/**
 * @brief Destructor
 * 
 * @param cat 
 */
void free_cat(cat_t *cat);

/**
 * @brief Moves cat from stack to heap
 */
cat_t *move_cat(cat_t *cat);

/**
 * @brief Input cat patient
 * 
 * @param cat 
 * @return int 
 */
int input_cat(FILE *file, cat_t *cat);

/**
 * @brief Asks for user cat input
 * 
 * @param cat
 * @return int 
 */
int prompt_cat(cat_t *cat);

/**
 * @brief Output cat patient
 * 
 * @param cat 
 */
void output_cat(FILE *file, const void *cat);

/**
 * @brief Free memory occupied by cat
 * 
 * @param cat 
 */
void destroy_patient(cat_t *cat);

/**
 * @brief Compares two dates
 * 
 * @param cat1 
 * @param cat2
 * @return int 
 */
int date_compare(const void *cat1, const void *cat2);

#endif /* __CAT_H__ */
