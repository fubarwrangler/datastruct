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
dlnode *dllist_create_node(void *data, size_t len);
void dllist_destroy_node(dlnode *node);

dlnode *dllist_get_index(dllist *list, size_t idx);

void dllist_swap(dllist *list, dlnode *n1, dlnode *n2);
dlnode *dllist_insert_after(dlnode *node, void *data, size_t len);
dlnode *dllist_insert_before(dlnode *node, void *data, size_t len);
dlnode *dllist_insert(dllist *list, void *data, size_t len);
dlnode *dllist_append(dllist *list, void *data, size_t len);
void dllist_delete(dllist *list, dlnode *node);

void dllist_apply_each(dllist *list, void (*fn)(void *));


#define DL_INDEX(l, n) dllist_get_index(l, n)

#endif
