#include <check.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define MAT_EPS 1e-6

#define assert_mat_eq(l, r) \
    ck_assert(l.data != NULL && r.data != NULL); \
    ck_assert(l.rows == r.rows && l.cols == r.cols); \
    for (size_t row = 0; row < l.rows; row++) \
        for (size_t col = 0; col < l.cols; col++) \
            ck_assert(fabs(l.data[row][col] - r.data[row][col]) < MAT_EPS);

#define MATRIX(rows, cols, ...) \
    _mat_construct(rows, cols, (data_t[]){ __VA_ARGS__ });

static matrix_t _mat_construct(size_t rows, size_t cols, data_t* data)
{
    matrix_t res;

    res.rows = rows;
    res.cols = cols;
    res.data = calloc(rows, sizeof(data_t *));

    for (size_t row = 0; row < rows; row++)
    {
        res.data[row] = malloc(cols * sizeof(data_t));
        for (size_t col = 0; col < cols; col++)
            res.data[row][col] = data[row * cols + col];
    }

    return res;
}

START_TEST(add_mats)
{
    matrix_t left = MATRIX(1, 1, 2.0);
    matrix_t right = MATRIX(1, 1, 3.0);

    matrix_t expected = MATRIX(1, 1, 5.0);
    matrix_t res = mat_null();

    status_t status = mat_add(&res, &left, &right);
    ck_assert_int_eq(status, success);
    assert_mat_eq(expected, res);

    mat_destroy(&left);
    mat_destroy(&right);
    mat_destroy(&res);
    mat_destroy(&expected);

    mat_add(&res, &left, &right);
}
END_TEST

START_TEST(mul_mats)
{
    matrix_t left = MATRIX(3, 4,
        2.0, -0.8,  4.3, 8.91,
          7,    1,    9,   -4,
        3.8,  1.9, -5.4,  4.5
    );
    matrix_t right = MATRIX(4, 5,
        3.0, 2.3, 3.4, 4.5, -5.6,
        6.6, 6.7,   7,   0,    4,
          6,  -3,   5,   2,    7,
          7,   3,  -6,   2,   -5
    );

    matrix_t expected = MATRIX(3, 5,
        88.89, 13.07, -30.76, 35.42, -28.85,
        53.6, -16.2, 99.8, 41.5, 47.8,
        23.04, 51.17, -27.78, 15.3, -73.98
    );
    matrix_t res = mat_null();

    status_t status = mat_mul(&res, &left, &right);
    ck_assert_int_eq(status, success);
    assert_mat_eq(expected, res);

    mat_destroy(&left);
    mat_destroy(&right);
    mat_destroy(&res);
    mat_destroy(&expected);

    mat_mul(&res, &left, &right);
}
END_TEST

START_TEST(solve_mats)
{
    matrix_t input = MATRIX(5, 6,
        87.34, 81.23, 77.22, -38.76, -20.72, -2873.4345,
        -13.89, 5.1, -99.08, -80.26, -19.86, 11510.589,
        26.66, -40.97, -62.24, 78.92, -27.09, 2249.4615,
        -45.32, 36.15, 28.17, 51.39, -14.74, -4981.8241,
        78.12, 63.84, 65.78, -64.11, 91.63, -4898.0772
    );

    matrix_t expect = MATRIX(5, 1,
        10.52,
        -13.87,
        -69.96,
        -50.4,
        -37.8
    );

    matrix_t result = mat_null();

    status_t status = mat_gauss_solve(&result, &input);
    ck_assert_int_eq(status, success);
    assert_mat_eq(result, expect);

    mat_destroy(&input);
    mat_destroy(&result);
    mat_destroy(&expect);

    mat_gauss_solve(&result, &input);
}
END_TEST

Suite *matrix_suite(void)
{
    Suite *suite = suite_create("matrix tests");
    TCase *tcase = tcase_create("core");

    suite_add_tcase(suite, tcase);

    tcase_add_test(tcase, add_mats);
    tcase_add_test(tcase, mul_mats);
    tcase_add_test(tcase, solve_mats);

    return suite;
}
