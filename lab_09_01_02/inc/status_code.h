#ifndef STATUS_CODE_H
#define STATUS_CODE_H

typedef enum
{
    success,
    cmd_args_error,
    input_error,
    file_io_error,
    search_error,
    memory_error
} status_t;

#endif // STATUS_CODE_H
