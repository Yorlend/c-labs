#include "tests.h"
#include "my_string.h"
#include <string.h>
#include <stdio.h>


int test_strpbrk_empty()
{
    const char *str1 = "";
    const char *str2 = "";
    char *expected = strpbrk(str1, str2);
    char *actual = my_strpbrk(str1, str2);

    if (expected == actual)
        return 0;
    return 1;
}

int test_strpbrk_no_match()
{
    const char *str1 = "some random string.";
    const char *str2 = "!q863619";
    char *expected = strpbrk(str1, str2);
    char *actual = my_strpbrk(str1, str2);

    if (expected == actual)
        return 0;
    return 1;
}

int test_strpbrk_plain()
{
    const char *str1 = "some random string.";
    const char *str2 = "382!r21a";
    char *expected = strpbrk(str1, str2);
    char *actual = my_strpbrk(str1, str2);

    if (expected == actual)
        return 0;
    return 1;
}

int test_strrchr_empty()
{
    const char *str = "";
    int c = '.';
    char *expected = strrchr(str, c);
    char *actual = my_strrchr(str, c);

    if (expected == actual)
        return 0;
    return 1;
}

int test_strrchr_no_match()
{
    const char *str = "some random string.";
    int c = '!';
    char *expected = strrchr(str, c);
    char *actual = my_strrchr(str, c);

    if (expected == actual)
        return 0;
    return 1; 
}

int test_strrchr_plain()
{
    const char *str = "some random! string.";
    int c = '!';
    char *expected = strrchr(str, c);
    char *actual = my_strrchr(str, c);

    if (expected == actual)
        return 0;
    return 1;    
}

int test_strpbrk()
{
    printf("TESTING STRPBRK ...");
    if (!test_strpbrk_empty())
        printf("TEST_EMPTY: PASSED\n");
    else
        printf("TEST_EMPTY: FAILED\n");
    if (!test_strpbrk_no_match())
        printf("TEST_NO_MATCH: PASSED\n");
    else
        printf("TEST_NO_MATCH: FAILED\n");
    if (!test_strpbrk_plain())
        printf("TEST_PLAIN: PASSED\n");
    else
        printf("TEST_PLAIN: FAILED\n");
    return test_strpbrk_empty() || test_strpbrk_no_match() || test_strpbrk_plain();
}

int test_strrchr()
{
    printf("TESTING STRRCHR ...");
    if (!test_strrchr_empty())
        printf("TEST_EMPTY: PASSED\n");
    else
        printf("TEST_EMPTY: FAILED\n");
    if (!test_strrchr_no_match())
        printf("TEST_NO_MATCH: PASSED\n");
    else
        printf("TEST_NO_MATCH: FAILED\n");
    if (!test_strrchr_plain())
        printf("TEST_PLAIN: PASSED\n");
    else
        printf("TEST_PLAIN: FAILED\n");
    return test_strrchr_empty() || test_strrchr_no_match() || test_strrchr_plain();
}

int test_my_string()
{
    return test_strpbrk() || test_strrchr();
}