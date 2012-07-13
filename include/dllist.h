#ifndef _DLLIST_H
#define _DLLIST_H

#define SEARCH_START_HEAD 0
#define SEARCH_START_TAIL 1

#define DL_INDEX(l, n) dllist_get_index(l, n)

typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} dlnode;


typedef struct dllist
{
    dlnode *head;
    dlnode *tail;
} dllist;

typedef void (*dllist_map_fn_t)(void *);
typedef void (*dllist_copy_fn_t)(void **);
typedef int (*dllist_cmp_fn_t)(void *, void *);


/**
 * Create/Destroy a new, empty doubly-linked-list object, returns NULL
 * on failure to allocate memory.
 */
dllist *dllist_init(void);
void dllist_destroy(dllist *l);
void dllist_destroy_callback(dllist *list, dllist_map_fn_t fn);

/**
 * Return the length of the given list, O(n): walks entire list
 */
size_t dllist_size(dllist *list);

/**
 * Return a pointer to a deep copy of *list, or NULL on failure
 */
dllist *dllist_copy(dllist *list);
dllist *dllist_deep_copy(dllist *lst, dllist_copy_fn_t cpy);


/**
 * Return the node at index idx, like x = list[idx], also callable as DL_INDEX,
 * see macro definition.  If idx > len(list), return last node in list.
 */
dlnode *dllist_get_index(dllist *list, size_t idx);

/**
 * Swap two nodes *n1 and *n2 in *list, updating list->head/tail as needed
 */
void dllist_swap(dllist *list, dlnode *n1, dlnode *n2);


dlnode *dllist_insert_after(dlnode *node, void *data);

/**
 * Insert a node at the begenning of *list, returns
 * pointer to new node, or NULL on failure
 */
dlnode *dllist_insert(dllist *list, void *data);

/**
 * Appends a new node to the end of *list.
 * Returns a pointer to the new node or NULL on failure
 */
dlnode *dllist_append(dllist *list, void *data);

/**
 * Delete *node from *list, updating ->head / ->tail as necessary
 */
void *dllist_delete(dllist *list, dlnode *node);

/**
 * Apply the function pointed to by (*fn) that takes a pointer to a ->data
 * element and (presumably) does something to it to each element of *list.
 */
void dllist_apply_each(dllist *list, dllist_map_fn_t fn);

/**
 * Join two lists, *second onto the end of *first, freeing the memory for
 * *second as it is no longer needed (the controlling structure).  Modifies
 * first->tail to point at new tail, returns pointer to single list.
 */
dllist *dllist_join(dllist *first, dllist *second);

/**
 * Reverse list in place.
 */
void dllist_reverse(dllist *list);

/**
 * Search the list sequentially for value, using (*cmp) to test equality, which
 * returns nonzero for not equal, 0 otherwise. Returns node where value is
 * found, or NULL if it isn't.
 */
dlnode *dllist_search(dllist *list, void *value, dllist_cmp_fn_t cmp);

/**
 * Return the index of the first appearence of given *value, -1 on not-found
 */
long dllist_find_index(dllist *list, void *value, dllist_cmp_fn_t cmp);

void dllist_sort(dllist *list, dllist_cmp_fn_t *cmp);


#endif
