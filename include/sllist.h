#ifndef _SLLIST_H
#define _SLLIST_H

typedef struct _llnode
{
    void *data;
    size_t len;
    struct _llnode *next;
}list_node;


typedef struct _linked_list
{
    size_t list_len;
    list_node *head;
} linked_list;

/* List create/destroy/measure */
linked_list *list_init(void);
void list_destroy(linked_list *list);
size_t list_size(linked_list *list);
list_node *list_get_index(linked_list *list, size_t index);
list_node *list_create_node(void *data, size_t len, char copy);
void list_destroy_node(list_node *node);
linked_list *list_copy(linked_list *list);

/* Inserting or deleting from the list */
list_node *list_delete_next(list_node *node);
list_node *list_delete_head(linked_list *list);
list_node *list_insert_head(linked_list *list, void *data, size_t len);
list_node *list_insert(linked_list *list, list_node *prev, void *data, size_t len);
list_node *list_insert_after(list_node *prev, void *data, size_t len);
list_node *list_insert_node(linked_list *list, list_node *newnode);
list_node *list_pop_next(list_node *node);
list_node *list_pop_head(linked_list *list);


/* List modification functions */
list_node *list_apply(list_node *node, void *(*fn)(void *));
list_node *list_reverse(linked_list *list);
list_node *list_swap_head(linked_list *list, list_node *p);
list_node *list_swap_next(list_node *p, list_node *q);
linked_list *list_apply_each(linked_list *list, void *(*fn)(void *));
linked_list *list_join(linked_list *first, linked_list *second);
list_node *list_join_after(list_node *node, linked_list *joinee);

int list_search(linked_list *list, void *compare, int (*search_fn)(void *, void *));
void list_shuffle(linked_list *list);


#endif
