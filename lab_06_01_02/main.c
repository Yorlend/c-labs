#include <stdio.h>
#include <string.h>
#include "status_code.h"
#include "file_io.h"
#include "constants.h"
#include "item.h"


int main(int argc, char **argv)
{
    status_t exit_code = success;
    FILE *f = NULL;

    if (argc < 2)
        exit_code = cmd_args_error;

    if (exit_code == success)
    {
        if (!exit_code)
            f = fopen(argv[1], "r");
        
        if (f == NULL)
            exit_code = file_io_error;
    }

    int items_len = 0;
    item_t items[STRUCT_MAX];

    if (exit_code == success)
        exit_code = read_items(f, items, &items_len);

    if (exit_code == success)
    {
        if (argc < 3)
        {
            sort_items(items, items_len);
            display_items(stdout, items, items_len);
        }
        else if (!strcmp(argv[2], "ALL"))
            display_items(stdout, items, items_len);
        else
            exit_code = display_startswith(stdout, items, items_len, argv[2]);
    }

    if (f != NULL)
        fclose(f);
    return exit_code;
}
