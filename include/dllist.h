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
size_t dllist_size(dllist *list);


dlnode *list_insert_head(dllist *list, dlnode *node);



void dllist_destroy_node(dlnode *node);
dlnode *dllist_swap(dllist *list, dlnode *a, dlnode *b);
dlnode *dllist_create_node(void *data, size_t len);
dlnode *dllist_insert_after(dlnode *node, void *data, size_t len);
dlnode *dllist_insert_head(dllist *list, void *data, size_t len);


#endif
