#include "status.h"
#include "action.h"
#include "process.h"

int main(int argc, const char **argv)
{
    if (argc < 2)
        return bad_cmd_opts;

    action_t action = undefined;
    status_t status = action_from_str(&action, argv[1]);

    if (status == success)
        status = dispatch_action(action, argc - 2, argv + 2);

    return status;
}
