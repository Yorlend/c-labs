#include <stdlib.h>
#include <check.h>
#include "items.h"

#define EPS 1e-6

#define ck_assert_dbl_eq(val1, val2) \
    ck_assert(fabs((val1) - (val2)) < EPS)

#define ck_assert_items_sorted(items)                       \
    for (size_t i = 0; i + 1 < items.size; i++)             \
    {                                                       \
        double density_1 = get_density(&items.data[i]);     \
        double density_2 = get_density(&items.data[i + 1]); \
        ck_assert(density_1 <= density_2);                   \
    }

START_TEST(sort_items_null)
{
    sort_items(NULL);
    ck_assert(true);
}
END_TEST

START_TEST(sort_items_data_null)
{
    items_t items = items_null();

    sort_items(&items);
    ck_assert(true);
}
END_TEST

START_TEST(sort_items_sorted)
{
    items_t items;
    items.size = 10;
    items.data = malloc(items.size * sizeof(item_t));

    for (size_t i = 0; i < items.size; i++)
    {
        double weight = 10.0 * (i + 1);
        double volume = 10.0;
        items.data[i] = create_item("item", weight, volume);
    }

    sort_items(&items);
    ck_assert_items_sorted(items);

    destroy_items(&items);
}
END_TEST

START_TEST(sort_items_shuffled)
{
    items_t items;
    items.size = 10;
    items.data = malloc(items.size * sizeof(item_t));

    for (size_t i = 0; i < items.size; i++)
    {
        double weight = 10.0 * (rand() % 10 + 1);
        double volume = 10.0;
        items.data[i] = create_item("item", weight, volume);
    }

    sort_items(&items);
    ck_assert_items_sorted(items);

    destroy_items(&items);
}
END_TEST

TCase *sort_items_tcase(void)
{
    TCase *tcase = tcase_create("sort_items");

    tcase_add_test(tcase, sort_items_null);
    tcase_add_test(tcase, sort_items_data_null);
    tcase_add_test(tcase, sort_items_sorted);
    tcase_add_test(tcase, sort_items_shuffled);

    return tcase;
}

Suite *items_suite(void)
{
    Suite *suite = suite_create("items");

    suite_add_tcase(suite, sort_items_tcase());

    return suite;
}
