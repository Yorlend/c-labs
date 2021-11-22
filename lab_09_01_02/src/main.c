#include <string.h>
#include "status_code.h"
#include "file_utils.h"
#include "items.h"


int main(int argc, char **argv)
{
    status_t exit_code = success;
    FILE *f = NULL;
    items_t items = items_null();

    if (argc < 2)
        exit_code = cmd_args_error;

    if (exit_code == success)
    {
        f = fopen(argv[1], "r");
        
        if (f == NULL)
            exit_code = file_io_error;
    }

    if (exit_code == success)
        exit_code = read_items(f, &items);

    if (exit_code == success)
    {
        if (argc < 3)
        {
            sort_items(&items);
            display_items(stdout, &items);
        }
        else if (!strcmp(argv[2], "ALL"))
            display_items(stdout, &items);
        else
            exit_code = display_items_startswith(stdout, &items, argv[2]);
    }

    if (f != NULL)
        fclose(f);

    destroy_items(&items);
    return exit_code;
}
