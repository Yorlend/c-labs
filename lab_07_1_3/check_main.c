#include <check.h>

Suite *sort_suite();
Suite *filter_suite();


int main()
{
    Suite *s = sort_suite();
    SRunner *runner = srunner_create(s);
    srunner_add_suite(runner, filter_suite());

    srunner_run_all(runner, CK_VERBOSE);
    int failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}
