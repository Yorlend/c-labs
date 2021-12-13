#include <check.h>
#include <stdlib.h>
#include "list.h"

#define ck_assert_list_eq(lst, ...) \
{ \
    int array[] = { __VA_ARGS__ }; \
    node_t *test = list_from_array(array, sizeof(array) / sizeof(int)); \
    node_t *l_node = lst, *t_node = test; \
    while (l_node != NULL || t_node != NULL) \
    { \
        if (l_node == NULL && t_node == NULL) \
            break; \
        ck_assert_ptr_ne(l_node, NULL); \
        ck_assert_ptr_ne(t_node, NULL); \
        ck_assert_int_eq(*(int*)l_node->data, *(int*)t_node->data); \
        l_node = l_node->next; \
        t_node = t_node->next; \
    } \
    smart_list_destroy(&test); \
}

static node_t *list_from_array(int* array, size_t size)
{
    node_t *list = NULL;
    node_t **tail = &list;

    for (size_t i = 0; i < size; i++)
    {
        int *data = malloc(sizeof(int));
        *data = array[i];
        *tail = node_init(data);
        tail = &(*tail)->next;
    }

    return list;
}

static void smart_list_destroy(node_t **list)
{
    for (node_t *node = *list; node != NULL; node = node->next)
        free(node->data);
    list_destroy(*list);
    *list = NULL;
}

static int int_cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

START_TEST(find_empty)
{
    node_t *list = NULL;

    int *elem = malloc(sizeof(int));
    *elem = 10;

    node_t *res = find(list, elem, int_cmp);
    ck_assert_ptr_eq(res, NULL);

    free(elem);
    elem = NULL;
}
END_TEST

START_TEST(find_failed)
{
    int array[] = {4, 2, 5, -7, 11};
    node_t *list = list_from_array(array, 5);

    int *elem = malloc(sizeof(int));
    *elem = 3;

    node_t *res = find(list, elem, int_cmp);
    ck_assert_ptr_eq(res, NULL);
    ck_assert_list_eq(list, 4, 2, 5, -7, 11);

    free(elem);
    smart_list_destroy(&list); 
}
END_TEST

START_TEST(find_success)
{
    int array[] = {4, 2, 5, -7, 11};
    node_t *list = list_from_array(array, 5);

    int *elem = malloc(sizeof(int));
    *elem = 5;

    node_t *res = find(list, elem, int_cmp);
    ck_assert_ptr_eq(res, list->next->next);
    ck_assert_list_eq(list, 4, 2, 5, -7, 11);

    free(elem);
    smart_list_destroy(&list); 
}
END_TEST

START_TEST(insert_empty)
{
    node_t *list = NULL;

    int *elem = malloc(sizeof(int));
    *elem = -32;

    insert(&list, node_init(elem), NULL);
    ck_assert_list_eq(list, -32);

    smart_list_destroy(&list);
}
END_TEST

START_TEST(insert_head)
{
    int array[] = {12, 6, -7, 3, -21, 0};
    node_t *list = list_from_array(array, 6);

    int *elem = malloc(sizeof(int));
    *elem = 5;

    printf("HEAD: \n%p\n\n", (void*)list);
    insert(&list, node_init(elem), list);
    ck_assert_list_eq(list, 5, 12, 6, -7, 3, -21, 0);

    smart_list_destroy(&list);
}
END_TEST

START_TEST(insert_body)
{
    int array[] = {12, 6, -7, 3, -21, 0};
    node_t *list = list_from_array(array, 6);

    int *elem = malloc(sizeof(int));
    *elem = 5;

    printf("BODY: \n%p\n\n", (void*)list);
    insert(&list, node_init(elem), list->next->next);
    ck_assert_list_eq(list, 12, 6, 5, -7, 3, -21, 0);

    smart_list_destroy(&list);
}
END_TEST

START_TEST(insert_tail)
{
    int array[] = {12, 6, -7};
    node_t *list = list_from_array(array, 3);

    int *elem = malloc(sizeof(int));
    *elem = 5;

    insert(&list, node_init(elem), NULL);
    ck_assert_list_eq(list, 12, 6, -7, 5);

    smart_list_destroy(&list);
}
END_TEST

START_TEST(remove_empty)
{
    node_t *list = NULL;

    remove_duplicates(&list, int_cmp);
    ck_assert_ptr_eq(list, NULL);
}
END_TEST

START_TEST(remove_nothing)
{
    int array[] = {1, 2, 4, 5, 7};
    node_t *list = list_from_array(array, 5);

    remove_duplicates(&list, int_cmp);
    ck_assert_list_eq(list, 1, 2, 4, 5, 7);

    smart_list_destroy(&list);
}
END_TEST

START_TEST(remove_something)
{
    int array[] = {1, 1, 1, 2, 3, 3};
    int *ptrs = malloc(sizeof(array));
    node_t *list = NULL;
    for (int i = 0; i < 6; i++)
    {
        ptrs[i] = array[i];
        insert(&list, node_init(ptrs + i), NULL);
    }

    remove_duplicates(&list, int_cmp);
    ck_assert_list_eq(list, 1, 2, 3);

    list_destroy(list);
    free(ptrs);
}
END_TEST

START_TEST(split_empty)
{
    node_t *list = NULL;
    node_t *back = NULL;

    front_back_split(list, &back);
    ck_assert_ptr_eq(back, NULL);
}
END_TEST

START_TEST(split_one)
{
    int *elem = malloc(sizeof(int));
    *elem = 3;

    node_t *list = node_init(elem);
    node_t *back = NULL;

    front_back_split(list, &back);
    ck_assert_list_eq(list, 3);
    ck_assert_ptr_eq(back, NULL);

    smart_list_destroy(&list);
}
END_TEST

START_TEST(split_even)
{
    int array[] = {4, 3, -6, -21, 804, -2};
    node_t *list = list_from_array(array, 6);
    node_t *back = NULL;

    front_back_split(list, &back);
    ck_assert_list_eq(list, 4, 3, -6);
    ck_assert_list_eq(back, -21, 804, -2);

    smart_list_destroy(&list);
    smart_list_destroy(&back);
}
END_TEST

START_TEST(split_odd)
{
    int array[] = {4, 3, -6, -21, 804};
    node_t *list = list_from_array(array, 5);
    node_t *back = NULL;

    front_back_split(list, &back);
    ck_assert_list_eq(list, 4, 3, -6);
    ck_assert_list_eq(back, -21, 804);

    smart_list_destroy(&list);
    smart_list_destroy(&back);
}
END_TEST

START_TEST(merge_empty)
{
    node_t *list_1 = NULL;
    node_t *list_2 = NULL;

    node_t *res = sorted_merge(&list_1, &list_2, int_cmp);
    ck_assert_ptr_eq(list_1, NULL);
    ck_assert_ptr_eq(list_2, NULL);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(merge_left)
{
    int array[] = {1, 3, 4, 4};
    node_t *list_1 = list_from_array(array, 4);
    node_t *list_2 = NULL;

    node_t *res = sorted_merge(&list_1, &list_2, int_cmp);
    ck_assert_ptr_eq(list_1, NULL);
    ck_assert_ptr_eq(list_2, NULL);
    ck_assert_list_eq(res, 1, 3, 4, 4);

    smart_list_destroy(&res);
}
END_TEST

START_TEST(merge_right)
{
    int array[] = {1, 3, 4, 4};
    node_t *list_1 = NULL;
    node_t *list_2 = list_from_array(array, 4);

    node_t *res = sorted_merge(&list_1, &list_2, int_cmp);
    ck_assert_ptr_eq(list_1, NULL);
    ck_assert_ptr_eq(list_2, NULL);
    ck_assert_list_eq(res, 1, 3, 4, 4);

    smart_list_destroy(&res);
}
END_TEST

START_TEST(merge_both)
{
    int array_1[] = {1, 3, 4, 4, 6};
    int array_2[] = {2, 3, 5};
    node_t *list_1 = list_from_array(array_1, 5);
    node_t *list_2 = list_from_array(array_2, 3);

    node_t *res = sorted_merge(&list_1, &list_2, int_cmp);
    ck_assert_ptr_eq(list_1, NULL);
    ck_assert_ptr_eq(list_2, NULL);
    ck_assert_list_eq(res, 1, 2, 3, 3, 4, 4, 5, 6);

    smart_list_destroy(&res);
}
END_TEST

START_TEST(sort_empty)
{
    node_t *list = NULL;

    node_t *res = sort(list, int_cmp);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(sort_one)
{
    int *elem = malloc(sizeof(int));
    *elem = 123;

    node_t *list = node_init(elem);

    node_t *res = sort(list, int_cmp);
    ck_assert_list_eq(res, 123);

    smart_list_destroy(&res);
}
END_TEST

START_TEST(sort_even)
{
    int array[] = {7, 3, -5, 4, -1, -2};
    node_t *list = list_from_array(array, 6);

    node_t *res = sort(list, int_cmp);
    ck_assert_list_eq(res, -5, -2, -1, 3, 4, 7);

    smart_list_destroy(&res);
}
END_TEST

START_TEST(sort_odd)
{
    int array[] = {7, 3, -5, 4, -1, -2, 6};
    node_t *list = list_from_array(array, 7);

    node_t *res = sort(list, int_cmp);
    ck_assert_list_eq(res, -5, -2, -1, 3, 4, 6, 7);

    smart_list_destroy(&res);
}
END_TEST

static TCase *find_case(void)
{
    TCase *tcase = tcase_create("find");

    tcase_add_test(tcase, find_success);
    tcase_add_test(tcase, find_empty);
    tcase_add_test(tcase, find_failed);

    return tcase;
}

static TCase *insert_case(void)
{
    TCase *tcase = tcase_create("insert");

    tcase_add_test(tcase, insert_empty);
    tcase_add_test(tcase, insert_head);
    tcase_add_test(tcase, insert_body);
    tcase_add_test(tcase, insert_tail);

    return tcase;
}

static TCase *remove_dups_case(void)
{
    TCase *tcase = tcase_create("remove_duplicates");

    tcase_add_test(tcase, remove_empty);
    tcase_add_test(tcase, remove_nothing);
    tcase_add_test(tcase, remove_something);

    return tcase;
}

static TCase *split_case(void)
{
    TCase *tcase = tcase_create("front_back_split");

    tcase_add_test(tcase, split_empty);
    tcase_add_test(tcase, split_one);
    tcase_add_test(tcase, split_even);
    tcase_add_test(tcase, split_odd);

    return tcase;
}

static TCase *merge_case(void)
{
    TCase *tcase = tcase_create("sorted_merge");

    tcase_add_test(tcase, merge_empty);
    tcase_add_test(tcase, merge_left);
    tcase_add_test(tcase, merge_right);
    tcase_add_test(tcase, merge_both);

    return tcase;
}

static TCase *sort_case(void)
{
    TCase *tcase = tcase_create("sort");

    tcase_add_test(tcase, sort_empty);
    tcase_add_test(tcase, sort_one);
    tcase_add_test(tcase, sort_even);
    tcase_add_test(tcase, sort_odd);

    return tcase;
}

Suite *list_suite(void)
{
    Suite *suite = suite_create("list suite");

    suite_add_tcase(suite, find_case());
    suite_add_tcase(suite, insert_case());
    suite_add_tcase(suite, remove_dups_case());
    suite_add_tcase(suite, split_case());
    suite_add_tcase(suite, merge_case());
    suite_add_tcase(suite, sort_case());

    return suite;
}
