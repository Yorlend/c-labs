#include <string.h>
#include "action.h"

status_t action_from_str(action_t *action, const char *str)
{
    if (action == NULL || str == NULL)
        return bad_func_args;

    if (strcmp(str, "a") == 0)
        *action = add;
    else if (strcmp(str, "m") == 0)
        *action = multiply;
    else if (strcmp(str, "o") == 0)
        *action = solve;
    else
        return invalid_action;

    return success;
}
