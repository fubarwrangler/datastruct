#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
        free(list);
    }
}

dlnode *dllist_insert_head(dllist *list, void *data, size_t len)
{
    dlnode *p, *q;

    p = malloc(sizeof(dlnode));
    if(p != NULL)
    {
        p->len = len;
        p->prev = NULL;

        p->data = malloc(len);
        if(p->data != NULL)
        {
            memmove(p->data, data, len);
            q = list->head;
            if(q != NULL)
                q->prev = p;
            list->head = p;
            p->next = q;
        }
        else
        {
            free(p);
            p = NULL;
            fprintf(stderr, "Library Error: dllist_insert_head--No memory for data");
        }
    }
    else
        fprintf(stderr, "Library Error: dllist_insert_head--No memory for new node");

    return p;
}

dlnode *dllist_insert_after(dlnode *node, void *data, size_t len)
{
    dlnode *p = NULL, *q = NULL;

    assert(node != NULL);

    p = malloc(sizeof (dlnode));

    if(p == NULL)
        fprintf(stderr, "dllist_insert_after: *node is NULL or no Memory\n");
    else
    {
        p->data = malloc(len);
        if(p->data == NULL)
        {
            fprintf(stderr, "dllist_insert_after: no memory for new data\n");
            free(p);
            p=NULL;
        }
        else
        {
            memmove(p->data, data, len);
            p->len = len;

            q = node->next;

            node->next = p;
            p->prev = node;
            p->next = q;
        }
    }
    return p;
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
    p->next = NULL;
    p->prev = NULL;
    return p;
}


void dllist_destroy_node(dlnode *node)
{
    free(node->data);
    free(node);
}

dlnode *dllist_swap(dllist *list, dlnode *a, dlnode *b)
{
    dlnode *p, *q;

    if(a->prev == NULL)
    {
        list->head = b;
        b->prev = NULL;
        b->next = a->next;
    }



}

size_t dllist_size(dllist *list)
{
    size_t ctr = 0;
    dlnode *p = NULL;
    p = list->head;
    assert(p->next != NULL);
    while((p = p->next))
        ctr++;
    return ctr;
}
