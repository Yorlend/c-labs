#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>


typedef int data_t;

typedef struct node
{
    int row;
    int col;
    data_t value;
    struct node *next;
} node_t;

typedef struct matrix
{
    node_t *head;
} matrix_t;

/**
 * @brief List node initializer
 * 
 * @param row matrix element's row
 * @param col matrix element's column
 * @param val matrix element's value
 * @return node_t* -- allocated node
 */
node_t *node_init(int row, int col, data_t val);

/**
 * @brief Initializes NULL matrix
 * 
 * @return matrix_t -- NULL matrix
 */
matrix_t m_init(void);

/**
 * @brief Pushes element to list's tail
 * 
 * @param mat matrix (list)
 * @param row matrix element's row
 * @param col matrix element's column
 * @param val matrix element's value
 * @return int 
 */
int m_push(matrix_t *mat, int row, int col, data_t val);

/**
 * @brief Prints the given matrix
 * 
 * @param mat given matrix
 */
void m_print(const matrix_t *mat);

/**
 * @brief Frees memory occupied by given matrix
 * 
 * @param mat given matrix
 */
void m_destroy(matrix_t *mat);

/**
 * @brief Matrix input
 * 
 * @param mat resulting matrix in coord form
 * @return int -- status code
 */
int m_input(matrix_t *mat);

/**
 * @brief Sum of two matrices
 * 
 * @param res resulting matrix
 * @param m1 left matrix
 * @param m2 right matrix
 * @return int -- status code
 */
void m_sum(matrix_t *res, const matrix_t *m1, const matrix_t *m2);

/**
 * @brief Matrix multiplication
 * 
 * @param res resulting matrix
 * @param m1 left matrix
 * @param m2 right matrix
 * @return int -- status code
 */
int m_mul(matrix_t *res, const matrix_t *m1, const matrix_t *m2);

/**
 * @brief Deletes row with max element from the given matrix
 * 
 * @param mat given matrix
 * @return int -- status code
 */
void m_maxrow_del(matrix_t *mat);

#endif /* __MATRIX_H__ */
