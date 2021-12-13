#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>


typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

/**
 * @brief Функция создания узла списка
 * 
 * @param data Указатель на элемент узла
 * @return node_t* -- указатель на созданный узел
 */
node_t *node_init(void *data);

/**
 * @brief Функция печати списка на экран
 * 
 * @param head указатель на голову списка
 * @param printer функция печати одного элемента списка
 */
void list_print(FILE *f, node_t *head,
void (*printer)(FILE *, const void *));

/**
 * @brief Очищает память, занимаемую списком
 * 
 * @param head указатель на голову списка
 */
void list_destroy(node_t *head);

/**
 * @brief Функция поиска элемента в списке
 * 
 * @param head Указатель на голову списка
 * @param data Указатель на элемент поиск которого производится
 * @param comparator Функция сравнения элементов списка
 * @return node_t* -- указатель на искомый узел
 */
node_t *find(node_t *head, const void *data,
int (*comparator)(const void *, const void *));

/**
 * @brief Функция вставки элемента в список перед указанным
 * 
 * @param head Указатель на голову списка
 * @param elem Указатель на узел, вставляемый в список
 * @param before Указатель на узел, перед которым происходит вставка
 */
void insert(node_t **head, node_t *elem, node_t *before);

/**
 * @brief Функция получает упорядоченный список и
 * оставляет в нем лишь первые вхождения каждого элемента
 * 
 * @param head Указатель на голову упорядоченного списка
 * @param comparator Функция сравнения элементов списка
 */
void remove_duplicates(node_t **head,
int (*comparator)(const void *, const void *));

/**
 * @brief Функция получает список и делит его на две половины
 * 
 * @param head указатель на голову списка
 * @param back указатель на указатель на вторую половину списка
 */
void front_back_split(node_t *head, node_t **back);

/**
 * @brief Функция объединяет два упорядоченных списка в один
 * 
 * @param head_a указатель на голову первого упорядоченного списка
 * @param head_b указатель на голову второго упорядоченного списка
 * @param comparator функция сравнения элементов списка
 * @return node_t* -- отсортированный список, полученный из двух исходных
 */
node_t *sorted_merge(node_t **head_a, node_t **head_b,
int (*comparator)(const void *, const void *));

/**
 * @brief Сортирует список рекурсивным алгоритмом сортировки слиянием
 * 
 * @param head указатель на голову списка
 * @param comparator функция сравнения элементов списка
 * @return node_t* -- указатель на голову нового, отсортированного списка
 */
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif /* __LIST_H__ */
