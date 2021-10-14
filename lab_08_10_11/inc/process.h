#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "status.h"
#include "action.h"
#include "matrix.h"

typedef status_t (*mat_bin_op_t)(matrix_t *, const matrix_t *, const matrix_t *);

status_t dispatch_action(action_t action, int argc, const char **argv);
status_t process_bin_op(int argc, const char **argv, mat_bin_op_t op);
status_t process_solve(int argc, const char **argv);

#endif /* __PROCESS_H__ */
