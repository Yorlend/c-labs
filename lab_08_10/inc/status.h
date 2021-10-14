#ifndef __STATUS_H__
#define __STATUS_H__

typedef enum
{
    success,
    failure,
    bad_cmd_opts,
    bad_func_args,
    invalid_action,
    bad_file,
    bad_matrix_format,
    bad_matrix_dims,
    memory_error,
    invalid_matrix,
    solve_error
} status_t;

#endif /* __STATUS_H__ */
