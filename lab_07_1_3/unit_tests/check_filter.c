#include <check.h>
#include "filter.h"


START_TEST(empty_array)
{
    int arr[] = { 0 };
    int *pb_dst = NULL, *pe_dst = NULL;

    status_t res = key(arr, arr, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, empty_array_error);
    ck_assert_ptr_eq(pb_dst, NULL);
    ck_assert_ptr_eq(pe_dst, NULL);
}
END_TEST

START_TEST(empty_result)
{
    int arr[] = { -3, 4, 2 };
    int *pb_dst = NULL, *pe_dst = NULL;

    status_t res = key(arr, arr + 3, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, filter_error);
    ck_assert_ptr_eq(pb_dst, NULL);
    ck_assert_ptr_eq(pe_dst, NULL);
}
END_TEST

START_TEST(full_result)
{
    int arr[] = { 3, 4, 2 };
    int *pb_dst = NULL, *pe_dst = NULL;

    status_t res = key(arr, arr + 3, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, success);
    ck_assert_ptr_eq(pb_dst + 3, pe_dst);
    ck_assert_int_eq(pb_dst[0], 3);
    ck_assert_int_eq(pb_dst[1], 4);
    ck_assert_int_eq(pb_dst[2], 2);
}
END_TEST

START_TEST(partial_result)
{
    int arr[] = { 3, 4, 2, -1, 4, 7 };
    int *pb_dst = NULL, *pe_dst = NULL;

    status_t res = key(arr, arr + 6, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, success);
    ck_assert_ptr_eq(pb_dst + 3, pe_dst);
    ck_assert_int_eq(pb_dst[0], 3);
    ck_assert_int_eq(pb_dst[1], 4);
    ck_assert_int_eq(pb_dst[2], 2);
}
END_TEST

Suite *filter_suite()
{
    Suite *suite = suite_create("filter");
    TCase *tcase = tcase_create("core");

    tcase_add_test(tcase, empty_array);
    tcase_add_test(tcase, empty_result);
    tcase_add_test(tcase, full_result);
    tcase_add_test(tcase, partial_result);
    suite_add_tcase(suite, tcase);

    return suite;
}
