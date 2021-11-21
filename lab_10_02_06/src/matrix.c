#include "matrix.h"
#include "error_types.h"
#include <stdlib.h>
#include <stdio.h>


node_t *node_init(int row, int col, data_t val)
{
    node_t *res = malloc(sizeof(node_t));

    res->row = row;
    res->col = col;
    res->value = val;
    res->next = NULL;

    return res;
}

matrix_t m_init(void)
{
    return (matrix_t){ .head = NULL };
}

static inline int cmp(node_t *n1, node_t *n2)
{
    int d_row = n1->row - n2->row, d_col = n2->col - n2->col;

    if (d_row == 0)
        return d_col;

    return d_row;
}

int m_push(matrix_t *mat, int row, int col, data_t val)
{
    node_t *node = node_init(row, col, val);

    if (node == NULL)
        return MEM_ERR;

    if (mat->head == NULL)
        mat->head = node;
    else
    {
        node_t *head = mat->head;
        while (head->next != NULL)
            head = head->next;
        head->next = node;
    }

    return SUCCESS;
}

static inline void node_print(const node_t *node)
{
    printf("%d %d %d ", node->row, node->col, node->value);
}

void m_print(const matrix_t *mat)
{
    node_t *head = mat->head;

    while (head != NULL)
    {
        node_print(head);
        head = head->next;
    }

    printf("\n");
}

void m_destroy(matrix_t *mat)
{
    while (mat->head != NULL)
    {
        node_t *tmp = mat->head;
        mat->head = mat->head->next;
        free(tmp);
    }
}

static inline int input_dims(int *rows, int *cols)
{
    if (scanf("%d%d", rows, cols) != 2)
        return INP_ERR;

    if (*rows < 1 || *cols < 1)
        return INP_ERR;

    return SUCCESS;
}

static inline int input_node(matrix_t *mat, int row, int col)
{
    int status = SUCCESS;
    int tmp = 0;
    
    if (scanf("%d", &tmp) != 1)
        status = INP_ERR;

    if (status == SUCCESS && tmp != 0)
        status = m_push(mat, row, col, tmp);
    
    return status;
}

int m_input(matrix_t *mat)
{
    int status = SUCCESS;
    int rows = 0, cols = 0;

    status = input_dims(&rows, &cols);

    if (status == SUCCESS)
    {
        for (int i = 0; i < rows && status == SUCCESS; i++)
            for (int j = 0; j < cols && status == SUCCESS; j++)
                status = input_node(mat, i, j);
    }

    if (status != SUCCESS)
        m_destroy(mat);

    return status;
}

void m_sum(matrix_t *res, const matrix_t *m1, const matrix_t *m2)
{
    node_t *h1 = m1->head, *h2 = m2->head;

    *res = m_init();

    while (h1 != NULL && h2 != NULL)
    {
        int cmp_res = cmp(h1, h2);
        if (cmp_res == 0)
        {
            m_push(res, h1->row, h1->col, h1->value + h2->value);
            h1 = h1->next;
            h2 = h2->next;
        }
        else if (cmp_res > 0)
        {
            m_push(res, h2->row, h2->col, h2->value);
            h2 = h2->next;
        }
        else
        {
            m_push(res, h1->row, h1->col, h1->value);
            h1 = h1->next;
        }
    }

    while (h1 != NULL)
    {
        m_push(res, h1->row, h1->col, h1->value);
        h1 = h1->next;
    }

    while (h2 != NULL)
    {
        m_push(res, h2->row, h2->col, h2->value);
        h2 = h2->next;
    }
}

static inline data_t m_get(const matrix_t *mat, int row, int col)
{
    for (node_t *node = mat->head; node != NULL; node = node->next)
        if (node->row == row && node->col == col)
            return node->value;

    return 0;
}

static inline int m_insert_node(node_t **before, int row, int col, data_t value)
{
    int status = SUCCESS;
    node_t *node = node_init(row, col, value);
    if (node == NULL)
        status = MEM_ERR;
    else
    {
        if (*before != NULL)
            node->next = *before;
        *before = node;
    }

    return status;
}

static inline int m_set_notnull(matrix_t *mat, int row, int col, data_t value)
{
    int status = SUCCESS;
    node_t **node = &mat->head;

    if (*node == NULL)
        status = m_insert_node(node, row, col, value);
    else
    {
        while (*node != NULL && (*node)->row < row)
            node = &(*node)->next;
        
        if (*node == NULL)
            status = m_insert_node(node, row, col, value);
        else if ((*node)->row == row)
        {
            while (*node != NULL && (*node)->col < col)
                node = &(*node)->next;

            if (*node == NULL)
                status = m_insert_node(node, row, col, value);
            else if ((*node)->col == col)
                (*node)->value = value;
            else
                status = m_insert_node(&(*node)->next, row, col, value);
        }
        else
            status = m_insert_node(&(*node)->next, row, col, value);
    }

    return status;
}

static inline int m_remove(matrix_t *mat, int row, int col)
{
    node_t **node = &mat->head;

    while (*node != NULL && (*node)->row == row && (*node)->col == col)
        node = &(*node)->next;

    if (*node != NULL)
    {
        node_t *tmp = (*node)->next;
        free(*node);
        *node = tmp;
    }

    return SUCCESS;
}

static inline int m_set(matrix_t *mat, int row, int col, data_t value)
{
    if (value == 0)
        return m_remove(mat, row, col);
    else
        return m_set_notnull(mat, row, col, value);
}

static void m_get_dims(const matrix_t *mat, int *rows, int *cols)
{
    *rows = 0;
    *cols = 0;
    for (node_t *node = mat->head; node != NULL; node = node->next)
    {
        if (node->row + 1 > *rows)
            *rows = node->row + 1;
        if (node->col + 1 > *cols)
            *cols = node->col + 1;
    }
}

int m_mul(matrix_t *res, const matrix_t *m1, const matrix_t *m2)
{
    int status = SUCCESS;
    *res = m_init();

    int rows1, cols1, rows2, cols2;
    m_get_dims(m1, &rows1, &cols1);
    m_get_dims(m2, &rows2, &cols2);

    int res_rows = rows1;
    int res_cols = cols2;
    int dim = cols1 < rows2 ? cols1 : rows2;

    for (int row = 0; status == SUCCESS && row < res_rows; row++)
    {
        for (int col = 0; status == SUCCESS && col < res_cols; col++)
        {
            data_t value = 0;
            for (int k = 0; k < dim; k++)
            {
                data_t v1 = m_get(m1, row, k);
                data_t v2 = m_get(m2, k, col);
                value += v1 * v2;
            }
            status = m_set(res, row, col, value);
        }
    }

    if (status != SUCCESS)
        m_destroy(res);

    return status;
}

static inline int find_max_row(const matrix_t *mat)
{
    int max_row = 0, max_val = 0;
    node_t *head = mat->head;

    if (head != NULL)
    {
        max_row = head->row;
        max_val = head->value;
        head = head->next;
    }

    while (head != NULL)
    {
        if (head->value > max_val)
        {
            max_row = head->row;
            max_val = head->value;
        }
        head = head->next;
    }
    
    return max_row;
}

void m_maxrow_del(matrix_t *mat)
{
    int max_row = find_max_row(mat);
    node_t *head = mat->head;

    while (head != NULL && head->next != NULL && head->next->row != max_row)
        head = head->next;

    while (head != NULL && head->next != NULL && head->next->row == max_row)
    {
        node_t *tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
    
    head = head->next;

    while (head != NULL)
    {
        head->row--;
        head = head->next;
    }
}
