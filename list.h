#ifndef _LIST_H
#define _LIST_H

typedef struct llnode
{
    void *data;
    size_t len;
    struct llnode *next;
}list_node;


typedef struct _linked_list
{
    size_t list_len;
    list_node *head;
} linked_list;

linked_list *list_init(void);
void list_destroy(linked_list *list);
list_node *list_delete_next(list_node *node);
linked_list *list_delete_head(linked_list *list);
list_node *list_insert_after(list_node *prev, void *data, size_t len);
list_node *list_apply(list_node *node, void *(*fn)(void *));
void list_reverse(linked_list *list);
size_t list_size(linked_list *list);
int list_search(linked_list *list, void *compare, int (*search_fn)(void *, void *));
list_node *list_insert_head(linked_list *list, void *data, size_t len);
list_node *list_insert(linked_list *list, list_node *prev, void *data, size_t len);
void list_shuffle(linked_list *list);


#endif

