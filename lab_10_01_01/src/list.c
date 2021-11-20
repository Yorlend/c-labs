#include "list.h"
#include <stddef.h>
#include <stdlib.h>

node_t *node_init(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (node != NULL)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

void list_print(FILE *f, node_t *head,
void (*printer)(FILE *, const void *))
{
    while (head != NULL)
    {
        printer(f, head->data);
        head = head->next;
    }
}

void list_destroy(node_t *head)
{
    while (head != NULL)
    {
        node_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}

node_t *find(node_t *head, const void *data,
int (*comparator)(const void*, const void*))
{
    while (head != NULL && comparator(head->data, data) != 0)
        head = head->next;

    return head;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == before)
    {
        elem->next = *head;
        *head = elem;
    }
    else
    {
        while ((*head)->next != NULL && (*head)->next != before)
            head = &(*head)->next;
        
        elem->next = (*head)->next;
        (*head)->next = elem;
    }
}

void remove_duplicates(node_t **head,
int (*comparator)(const void*, const void*))
{
    while (*head != NULL)
    {
        node_t *next = (*head)->next;
        while (next != NULL && comparator(next->data, (*head)->data) == 0)
        {
            (*head)->next = next->next;
            free(next);
            next = (*head)->next;
        }

        head = &(*head)->next; 
    }
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL)
        return;

    node_t *end_ptr = head;

    while (end_ptr->next != NULL && end_ptr->next->next != NULL)
    {
        head = head->next;
        end_ptr = end_ptr->next->next;
    }

    *back = head->next;
    head->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b,
int (*comparator)(const void *, const void *))
{
    node_t *head = NULL;
    node_t **tail = &head;

    node_t *node_a = *head_a;
    node_t *node_b = *head_b;


    while (node_a != NULL && node_b != NULL)
    {
        if (comparator(node_a->data, node_b->data) > 0)
        {
            *tail = node_b;
            node_b = node_b->next;
        }
        else
        {
            *tail = node_a;
            node_a = node_a->next;
        }

        tail = &((*tail)->next);
    }

    if (node_a != NULL)
        *tail = node_a;
    else
        *tail = node_b;

    *head_a = NULL;
    *head_b = NULL;

    return head;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head != NULL && head->next != NULL)
    {
        node_t *back = NULL;
        front_back_split(head, &back);

        head = sort(head, comparator);
        back = sort(back, comparator);
        head = sorted_merge(&head, &back, comparator);
    }

    return head;
}
