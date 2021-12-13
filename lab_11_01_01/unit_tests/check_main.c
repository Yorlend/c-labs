#include <check.h>

TCase *my_snprintf_case(void);

int main(void)
{
    Suite *suite = suite_create("my_snprintf");

    SRunner *runner = srunner_create(suite);

    suite_add_tcase(suite, my_snprintf_case());

    srunner_run_all(runner, CK_VERBOSE);

    int failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}