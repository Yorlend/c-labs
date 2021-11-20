#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cat.h"
#include "list.h"
#include "actions.h"


static void cat_list_destroy(node_t **list)
{
    for (node_t *node = *list; node != NULL; node = node->next)
    {
        free_cat(node->data);
        free(node->data);
    }
    list_destroy(*list);
    *list = NULL;
}

static int input_cat_list_file(node_t **list, FILE *file)
{
    int status = EXIT_SUCCESS;

    while (true)
    {
        cat_t tmp_cat = null_cat();
        status = input_cat(file, &tmp_cat);
        if (status != EXIT_SUCCESS)
        {
            status = EXIT_SUCCESS;
            break;
        }

        cat_t *heap_cat = move_cat(&tmp_cat);
        if (heap_cat == NULL)
        {
            status = EXIT_FAILURE;
            free_cat(&tmp_cat);
            break;
        }

        node_t *node = node_init(heap_cat);
        if (node == NULL)
        {
            status = EXIT_FAILURE;
            free_cat(heap_cat);
            free(heap_cat);
            break;
        }

        insert(list, node, NULL);
    }

    if (status != EXIT_SUCCESS)
        cat_list_destroy(list);

    return status;
}

static int input_cat_list(node_t **list, const char *filename)
{
    int status = EXIT_SUCCESS;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        status = EXIT_FAILURE;
    
    if (status == EXIT_SUCCESS)
        status = input_cat_list_file(list, file);

    if (file != NULL)
        fclose(file);
        
    return status;
}

static int str_compare(const cat_t *cat, const char *str)
{
    return strcmp(cat->name, str);
}

int action_find(const char *filename, const char *substr)
{
    node_t *list = NULL;
    int status = input_cat_list(&list, filename);
    
    if (status == EXIT_SUCCESS)
    {
        node_t *node = find(list, substr, str_compare);

        if (node != NULL)
            output_cat(stdout, node->data);
        
        cat_list_destroy(&list);
    }

    return status;
}

int action_sort(const char *filename)
{
    node_t *list = NULL;
    int status = input_cat_list(&list, filename);

    if (status == EXIT_SUCCESS)
    {
        list = sort(list, date_compare);
        list_print(stdout, list, output_cat);

        cat_list_destroy(&list);
    }

    return status;
}

int action_insert(const char *filename)
{
    node_t *list = NULL;
    int status = input_cat_list(&list, filename);

    if (status == EXIT_SUCCESS)
    {
        cat_t tmp_cat = null_cat();
        node_t *node = NULL;
        status = prompt_cat(&tmp_cat);
        if (status == EXIT_SUCCESS)
            node = node_init(move_cat(&tmp_cat));
        
        if (status == EXIT_SUCCESS && node != NULL)
            insert(&list, node, NULL);
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
        status = EXIT_FAILURE;
    else
    {
        list_print(file, list, output_cat);
        fclose(file);
    }

    return status;
}
