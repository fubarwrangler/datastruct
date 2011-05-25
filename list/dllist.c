#include <stdio.h>
#include <stdlib.h>

#include "dllist.h"


dllist *dllist_init(void)
{
    dllist *list;

    list = malloc(sizeof(dllist));

    if(list != NULL)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
        fprintf(stderr, "dllist_init: no memory for new list instance\n");

    return list;
}


void dllist_destroy(dllist *list)
{
    dlnode *p, *q;
    if (list != NULL)
    {
        p = list->head;
        while(p)
        {
            q = p->next;
            free(p->data);
            free(p);
            p = q;
        }
    }
}


dlnode *dllist_insert_head(dllist *list, dlnode *node)
{
    dlnode *p;

    p = list->head;
    list->head = node;
    node->prev = NULL;
    node->next = p;
    return node->next;
}

dlnode *dllist_insert_after(dlnode *node, dlnode *newnode)
{
    dlnode *p, *q;

    if(node == NULL)
    {
        fprintf(stderr, "dllist_insert_after: *node is NULL\n");
        return NULL;
    }

    if(node->next == NULL)
    {
        node->next = newnode;
        newnode->prev = node;
        newnode->next = NULL;
    }

    p = node->next;

    node->next = newnode;
    newnode->prev = node;
    newnode->next = p->next;
    p->prev = newnode;

    return node->next;
}

dlnode *dllist_create_node(void *data, size_t len)
{
    dlnode *p;

    p = malloc(sizeof(dlnode));
    if(p == NULL)
    {
        fprintf(stderr, "dllist_create_node: no mem for new node\n");
        return NULL;
    }

    p->data = malloc(len);
    if (p->data == NULL)
    {
        fprintf(stderr, "dllist_create_node: no mem for new node's data\n");
        free(p);
        return NULL;
    }
    memmove(p->data, data, len);
    p->len = len;
    return p;
}


void dllist_destroy_node(dlnode *node)
{
    free(node->data);
    free(node);
}

dlnode *dllist_swap(dllist *list, node *a, node *b)
{
    dlnode *p, *q;

    if(a->prev == NULL)
    {
        list->head = b;
        b->prev = NULL;
        b->next = a->next;
    }



}

