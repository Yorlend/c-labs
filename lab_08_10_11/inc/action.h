#ifndef __ACTION_H__
#define __ACTION_H__

#include "status.h"

typedef enum
{
    undefined,
    add,
    multiply,
    solve
} action_t;

status_t action_from_str(action_t *action, const char *str);

#endif /* __ACTION_H__ */
