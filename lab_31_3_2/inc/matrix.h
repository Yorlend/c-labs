#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdbool.h>

typedef int data_t;

typedef struct matrix
{
    int rows;
    int cols;
    data_t **data;
} matrix_t;


/**
 * @brief Создает пустую матрицу (null)
 * 
 * @return matrix_t 
 */
matrix_t mat_null(void);

/**
 * @brief Освобождает память из-под матрицы
 * 
 * @param mat (матрица, память которой очищается)
 */
void mat_free(matrix_t* mat);

/**
 * @brief Проверка - корректна ли матрица (не null)
 * 
 * @param mat проверяемая матрица
 * @return true 
 * @return false 
 */
bool mat_is_null(const matrix_t* mat);

/**
 * @brief Читает матрицу из файла по файловому указателю
 * 
 * @param file файловый указатель
 * @param mat выходная матрица
 * @return int (код ошибки)
 */
int mat_readf(FILE* file, matrix_t* mat);

/**
 * @brief Читает матрицу по имени файла
 * 
 * @param mat выходная матрица
 * @param filename имя входного файла
 * @return int (код ошибки)
 */
int mat_read(matrix_t* mat, const char* filename);

/**
 * @brief Выводит матрицу в файл / на экран (stdout)
 * 
 * @param file выходной файл
 * @param mat матрица
 * @return int (код ошибки)
 */
int mat_writef(FILE* file, matrix_t* mat);

/**
 * @brief Решает задачу сортировки необходимых элементов в массиве
 * 
 * @param mat исходная матрица
 * @return int (код ошибки)
 */
int mat_operate(matrix_t* mat);

#endif /* __MATRIX_H__ */
