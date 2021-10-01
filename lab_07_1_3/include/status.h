#ifndef __STATUS_H__
#define __STATUS_H__

typedef enum
{
    success,
    file_error,
    args_error,
    input_error,

    filter_error,
    func_args_error,
    empty_array_error,
    mem_error
} status_t;

#endif // __STATUS_H__
