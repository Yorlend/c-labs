#include <check.h>

Suite *matrix_suite(void);


int main(void)
{
    Suite *suite = matrix_suite();
    SRunner *runner = srunner_create(suite);

    // srunner_add_suite(runner, suite);

    srunner_run_all(runner, CK_VERBOSE);

    int nfailed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return nfailed;
}
