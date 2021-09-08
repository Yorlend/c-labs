#ifndef STATUS_CODE_H
#define STATUS_CODE_H

typedef enum
{
    SUCCESS,
    CMD_ARGS_ERROR,
    INPUT_ERROR,
    FILE_IO_ERROR,
    SEARCH_ERROR
} status_t;

#endif // STATUS_CODE_H
