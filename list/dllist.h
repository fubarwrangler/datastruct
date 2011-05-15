#ifndef _DLLIST_H
#define _DLLIST_H


typedef struct node
{
    size_t len;
    void *data;
    struct node *next;
} dlnode;


typedef struct dllist
{
    dlnode *head;
} dllist;


dllist *dllist_init(void);
void dllist_destroy(dllist *l);












#endif
