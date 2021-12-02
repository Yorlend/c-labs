#include <check.h>
#include <stdlib.h>
#include <limits.h>
#include <mystring.h>
#include <string.h>
#include <stdio.h>


#define assert_snprintf(format, ...) \
    { \
        size_t size = (size_t) snprintf(NULL, 0, format, __VA_ARGS__); \
        char *s1 = malloc(size), *s2 = malloc(size); \
        for (size_t n = size / 2; n < size; n++) \
        { \
            int res = snprintf(s1, n, format, __VA_ARGS__); \
            int my_res = my_snprintf(s2, n, format, __VA_ARGS__); \
            \
            ck_assert_str_eq(s1, s2); \
            ck_assert_int_eq(res, my_res); \
        } \
        free(s1); \
        free(s2); \
    } 

START_TEST(string_format)
{
    assert_snprintf("Given string: %s", "string");
}
END_TEST

START_TEST(short_format)
{
    assert_snprintf("Number: %hi", 999);
}
END_TEST

START_TEST(short_overflow)
{
    assert_snprintf("Overflow: %hi", 999999);
}
END_TEST

START_TEST(short_underflow)
{
    assert_snprintf("Underflow: %hi", -999999);
}
END_TEST

START_TEST(zero_short)
{
    assert_snprintf("Zero: %hi", 0);
}
END_TEST

START_TEST(mixed)
{
    assert_snprintf("%s goes for $%hi", "Macboook", 1600);
}
END_TEST

START_TEST(short_min)
{
    assert_snprintf("SHORT MIN: %hi", SHRT_MIN);
}
END_TEST

START_TEST(short_max)
{
    assert_snprintf("SHORT MAX: %hi", SHRT_MAX);
}
END_TEST

TCase *my_snprintf_case(void)
{
    TCase *tcase = tcase_create("my_snprintf");

    tcase_add_test(tcase, string_format);
    tcase_add_test(tcase, short_format);
    tcase_add_test(tcase, short_overflow);
    tcase_add_test(tcase, short_underflow);
    tcase_add_test(tcase, zero_short);
    tcase_add_test(tcase, mixed);
    tcase_add_test(tcase, short_min);
    tcase_add_test(tcase, short_max);

    return tcase;
}

