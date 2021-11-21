#include <check.h>
#include <stdlib.h>
#include <stdarg.h>
#include "matrix.h"
#include "error_types.h"

#define ck_assert_mat_eq(mat, rows, cols, ...) \
{ \
    data_t __exp[] = { __VA_ARGS__ }; \
    data_t __act[rows * cols] = { 0 }; \
 \
    for (node_t *node = mat.head; node != NULL; node = node->next) \
    { \
        ck_assert_int_lt(node->row, rows); \
        ck_assert_int_lt(node->col, cols); \
        __act[node->row * cols + node->col] = node->value; \
    } \
 \
    for (int row = 0; row < rows; row++) \
    { \
        for (int col = 0; col < cols; col++) \
        { \
            data_t exp = __exp[row * cols + col]; \
            data_t act = __act[row * cols + col]; \
            ck_assert(exp == act); \
        } \
    } \
}

matrix_t mat_from(int rows, int cols, ...)
{
    matrix_t res = m_init();
    node_t **tail = &res.head;

    va_list var_args;
    va_start(var_args, cols);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            int val = va_arg(var_args, int);
            if (val != 0)
            {
                *tail = node_init(row, col, val);
                tail = &(*tail)->next;
            }
        }
    }

    va_end(var_args);
    return res;
}

START_TEST(sum_null_null)
{
    matrix_t left = m_init();
    matrix_t right = m_init();
    matrix_t res = m_init();

    int status = m_sum(&res, &left, &right);
    ck_assert_ptr_eq(res.head, NULL);
    ck_assert_int_eq(status, OP_ERR);

    m_destroy(&left);
    m_destroy(&right);
    m_destroy(&res);
}
END_TEST

START_TEST(sum_to_null)
{
    matrix_t left = mat_from(1, 1, 53);
    matrix_t right = mat_from(1, 1, -53);
    matrix_t res = m_init();

    int status = m_sum(&res, &left, &right);
    ck_assert_ptr_eq(res.head, NULL);
    ck_assert_int_eq(status, OP_ERR);

    m_destroy(&left);
    m_destroy(&right);
    m_destroy(&res);
}
END_TEST

START_TEST(sum_success)
{
    matrix_t left = mat_from(1, 1, 53);
    matrix_t right = mat_from(1, 1, 53);
    matrix_t res = m_init();

    int status = m_sum(&res, &left, &right);
    ck_assert_mat_eq(res, 1, 1, 106);
    ck_assert_int_eq(status, SUCCESS);

    m_destroy(&left);
    m_destroy(&right);
    m_destroy(&res);
}
END_TEST

START_TEST(mul_null_null)
{
    matrix_t left = m_init();
    matrix_t right = m_init();
    matrix_t res = m_init();

    int status = m_mul(&res, &left, &right);
    ck_assert_ptr_eq(res.head, NULL);
    ck_assert_int_eq(status, OP_ERR);

    m_destroy(&left);
    m_destroy(&right);
    m_destroy(&res);
}
END_TEST

START_TEST(mul_to_null)
{
    matrix_t left = mat_from(1, 2, 0, -4);
    matrix_t right = mat_from(1, 1, 69, 0);
    matrix_t res = m_init();

    int status = m_mul(&res, &left, &right);
    ck_assert_ptr_eq(res.head, NULL);
    ck_assert_int_eq(status, OP_ERR);

    m_destroy(&left);
    m_destroy(&right);
    m_destroy(&res);
}
END_TEST

START_TEST(mul_success)
{
    matrix_t left = mat_from(1, 2, 1, -4);
    matrix_t right = mat_from(2, 1, 69, 2);
    matrix_t res = m_init();

    int status = m_mul(&res, &left, &right);
    ck_assert_mat_eq(res, 1, 1, 61);
    ck_assert_int_eq(status, SUCCESS);

    m_destroy(&left);
    m_destroy(&right);
    m_destroy(&res);
}
END_TEST

START_TEST(lin_from_null)
{
    matrix_t mat = m_init();
    
    int status = m_maxrow_del(&mat);
    ck_assert_int_eq(status, OP_ERR);
    ck_assert_ptr_eq(mat.head, NULL);
    
    m_destroy(&mat);
}
END_TEST

START_TEST(lin_to_null)
{
    matrix_t mat = mat_from(2, 2, 2, 1, 0, 0);
    
    int status = m_maxrow_del(&mat);
    ck_assert_int_eq(status, OP_ERR);
    ck_assert_ptr_eq(mat.head, NULL);
    
    m_destroy(&mat);
}
END_TEST

START_TEST(lin_success)
{
    matrix_t mat = mat_from(3, 3, 0, 0, 0, 1, 2, 3, -4, 0, 0);
    
    int status = m_maxrow_del(&mat);
    ck_assert_int_eq(status, SUCCESS);
    ck_assert_mat_eq(mat, 2, 3, 0, 0, 0, -4, 0, 0);
    
    m_destroy(&mat);
}
END_TEST

TCase *sum_case(void)
{
    TCase *tcase = tcase_create("m_sum");

    tcase_add_test(tcase, sum_null_null);
    tcase_add_test(tcase, sum_to_null);
    tcase_add_test(tcase, sum_success);

    return tcase;
}

TCase *mul_case(void)
{
    TCase *tcase = tcase_create("m_mul");

    tcase_add_test(tcase, mul_null_null);
    tcase_add_test(tcase, mul_to_null);
    tcase_add_test(tcase, mul_success);

    return tcase;
}

TCase *lin_case(void)
{
    TCase *tcase = tcase_create("m_maxrow_del");

    tcase_add_test(tcase, lin_from_null);
    tcase_add_test(tcase, lin_to_null);
    tcase_add_test(tcase, lin_success);

    return tcase;
}

Suite *matrix_suite(void)
{
    Suite *suite = suite_create("matrix");

    suite_add_tcase(suite, sum_case());
    suite_add_tcase(suite, mul_case());
    suite_add_tcase(suite, lin_case());

    return suite;
}
