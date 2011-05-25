#ifndef _DLLIST_H
#define _DLLIST_H


typedef struct node
{
    size_t len;
    void *data;
    struct node *next;
    struct node *prev;
} dlnode;


typedef struct dllist
{
    dlnode *head;
    dlnode *tail;
} dllist;


dllist *dllist_init(void);
void dllist_destroy(dllist *l);


dlnode *list_insert_head(dllist *list, dlnode *node);









#endif
