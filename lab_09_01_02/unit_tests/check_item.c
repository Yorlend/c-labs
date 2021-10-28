#include <check.h>
#include <math.h>
#include "item.h"

#define EPS 1e-6

#define ck_assert_dbl_eq(val1, val2) \
    ck_assert(fabs((val1) - (val2)) < EPS)

START_TEST(create_item_null_name)
{
    item_t item = create_item(NULL, 1.2, 3.4);

    ck_assert_ptr_eq(item.name, NULL);
    ck_assert_dbl_eq(item.volume, 0.0);
    ck_assert_dbl_eq(item.weight, 0.0);
}
END_TEST

START_TEST(create_item_empty_name)
{
    item_t item = create_item("", 1.2, 3.4);

    ck_assert_ptr_eq(item.name, NULL);
    ck_assert_dbl_eq(item.volume, 0.0);
    ck_assert_dbl_eq(item.weight, 0.0);
}
END_TEST

START_TEST(create_item_ok)
{
    item_t item = create_item("item", 1.2, 3.4);

    ck_assert_str_eq(item.name, "item");
    ck_assert_dbl_eq(item.weight, 1.2);
    ck_assert_dbl_eq(item.volume, 3.4);

    destroy_item(&item);
}
END_TEST

START_TEST(starts_with_null)
{
    item_t item = create_item("item", 1.2, 3.4);

    bool result = starts_with(&item, NULL);
    ck_assert(result == false);

    destroy_item(&item);
}
END_TEST

START_TEST(starts_with_empty)
{
    item_t item = create_item("item", 1.2, 3.4);

    bool result = starts_with(&item, "");
    ck_assert(result == true);

    destroy_item(&item);
}
END_TEST

START_TEST(starts_with_yes)
{
    item_t item = create_item("item", 1.2, 3.4);

    bool result = starts_with(&item, "it");
    ck_assert(result == true);

    destroy_item(&item);
}
END_TEST

START_TEST(starts_with_no)
{
    item_t item = create_item("item", 1.2, 3.4);

    bool result = starts_with(&item, "em");
    ck_assert(result == false);

    destroy_item(&item);
}
END_TEST

START_TEST(get_density_null)
{
    double result = get_density(NULL);

    ck_assert(isnan(result));
}
END_TEST

START_TEST(get_density_bad)
{
    item_t item = create_item("item", 1.2, 0.0);
    double result = get_density(&item);

    ck_assert(isnan(result));

    destroy_item(&item);
}
END_TEST

START_TEST(get_density_ok)
{
    item_t item = create_item("item", 1.2, 3.4);
    double result = get_density(&item);

    ck_assert_dbl_eq(result, 1.2 / 3.4);

    destroy_item(&item);
}
END_TEST

START_TEST(compare_items_null)
{
    double result = compare_items(NULL, NULL);

    ck_assert(isnan(result));
}
END_TEST

START_TEST(compare_items_ok)
{
    item_t item_1 = create_item("item_1", 1.2, 3.4);
    item_t item_2 = create_item("item_2", 5.6, 7.8);

    double result_1 = compare_items(&item_1, &item_2);
    double result_2 = compare_items(&item_2, &item_1);

    ck_assert(result_1 < 0.0);
    ck_assert_dbl_eq(result_1, -result_2);

    destroy_item(&item_1);
    destroy_item(&item_2);
}
END_TEST

TCase *create_item_tcase(void)
{
    TCase *tcase = tcase_create("create_item");

    tcase_add_test(tcase, create_item_null_name);
    tcase_add_test(tcase, create_item_empty_name);
    tcase_add_test(tcase, create_item_ok);

    return tcase;
}

TCase *starts_with_tcase(void)
{
    TCase *tcase = tcase_create("starts_with");

    tcase_add_test(tcase, starts_with_null);
    tcase_add_test(tcase, starts_with_empty);
    tcase_add_test(tcase, starts_with_yes);
    tcase_add_test(tcase, starts_with_no);

    return tcase;
}

TCase *get_density_tcase(void)
{
    TCase *tcase = tcase_create("get_density");

    tcase_add_test(tcase, get_density_null);
    tcase_add_test(tcase, get_density_bad);
    tcase_add_test(tcase, get_density_ok);

    return tcase;
}

TCase *compare_items_tcase(void)
{
    TCase *tcase = tcase_create("compare_items");

    tcase_add_test(tcase, compare_items_null);
    tcase_add_test(tcase, compare_items_ok);

    return tcase;
}

Suite *item_suite(void)
{
    Suite *suite = suite_create("item");

    suite_add_tcase(suite, create_item_tcase());
    suite_add_tcase(suite, starts_with_tcase());
    suite_add_tcase(suite, get_density_tcase());
    suite_add_tcase(suite, compare_items_tcase());

    return suite;
}
