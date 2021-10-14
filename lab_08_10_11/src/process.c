#include "process.h"

status_t dispatch_action(action_t action, int argc, const char **argv)
{
    switch (action)
    {
    case add:
        return process_bin_op(argc, argv, mat_add);

    case multiply:
        return process_bin_op(argc, argv, mat_mul);

    case solve:
        return process_solve(argc, argv);

    default:
        return invalid_action;
    }
}

status_t process_bin_op(int argc, const char **argv, mat_bin_op_t op)
{
    if (argv == NULL || op == NULL)
        return bad_func_args;

    if (argc < 3)
        return bad_cmd_opts;

    matrix_t left_mat = mat_null();
    matrix_t right_mat = mat_null();
    matrix_t res_mat = mat_null();

    // load input matrices
    status_t status = mat_read(&left_mat, argv[0]);
    if (status == success)
        status = mat_read(&right_mat, argv[1]);

    // apply operation
    if (status == success)
        status = op(&res_mat, &left_mat, &right_mat);

    // save result
    if (status == success)
        status = mat_write(&res_mat, argv[2]);

    mat_destroy(&left_mat);
    mat_destroy(&right_mat);
    mat_destroy(&res_mat);

    return status;
}

status_t process_solve(int argc, const char **argv)
{
    if (argv == NULL)
        return bad_func_args;

    if (argc < 2)
        return bad_cmd_opts;

    matrix_t input_mat = mat_null();
    matrix_t output_mat = mat_null();

    status_t status = mat_read(&input_mat, argv[0]);

    if (status == success)
        status = mat_gauss_solve(&output_mat, &input_mat);

    if (status == success)
        status = mat_write(&output_mat, argv[1]);

    mat_destroy(&input_mat);
    mat_destroy(&output_mat);

    return status;
}
