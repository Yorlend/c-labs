#include <check.h>
#include <stdbool.h>
#include "sort.h"


int cmp(const void *v1, const void *v2)
{
    return *(int*)v1 - *(int*)v2;
}

START_TEST(empty_array)
{
    int arr[] = { 0 };

    mysort(arr, 0, sizeof(int), cmp);

    ck_assert(true);
}
END_TEST

START_TEST(sorted_array)
{
    int arr[] = { 1, 3, 4, 7, 9 };

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), cmp);

    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 3);
    ck_assert_int_eq(arr[2], 4);
    ck_assert_int_eq(arr[3], 7);
    ck_assert_int_eq(arr[4], 9);
}
END_TEST

START_TEST(unsorted_array)
{
    int arr[] = { 7, 9, 1, 4, 3 };

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), cmp);

    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 3);
    ck_assert_int_eq(arr[2], 4);
    ck_assert_int_eq(arr[3], 7);
    ck_assert_int_eq(arr[4], 9);
}
END_TEST

Suite *sort_suite()
{
    Suite *suite = suite_create("sort");
    TCase *tcase = tcase_create("core");

    tcase_add_test(tcase, empty_array);
    tcase_add_test(tcase, sorted_array);
    tcase_add_test(tcase, unsorted_array);
    suite_add_tcase(suite, tcase);

    return suite;
}
