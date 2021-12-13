#include <check.h>

Suite *matrix_suite(void);

int main(void)
{
    SRunner *runner = srunner_create(matrix_suite());

    srunner_run_all(runner, CK_VERBOSE);

    int nfailed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return nfailed;
}
