#include <stdio.h>
#include "my_string.h"
#include "tests.h"


int main(void)
{
    test_my_string();
    const char *str1 = "abc";
    char *str = my_strrchr(str1, 0);

    printf("%s\n", str);

    return 0;
}