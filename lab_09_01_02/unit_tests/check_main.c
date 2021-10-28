#include <check.h>

Suite *item_suite(void);
Suite *items_suite(void);

int main(void)
{
    SRunner *srunner = srunner_create(item_suite());

    srunner_add_suite(srunner, items_suite());

    srunner_run_all(srunner, CK_VERBOSE);

    int ntests_failed = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return ntests_failed;
}
