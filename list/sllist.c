#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>

#include "sllist.h"

/** list_init()
 *  Allocates a new linked list and returns a pointer to it, will possibly
 *  fail on memory allocation error, returning NULL instead.
 *  @arg -- None
 *  @return -- An allocated link list object with a null head node
 */
linked_list *list_init(void)
{
    linked_list *lst;

    lst = malloc(sizeof(linked_list));
    if(lst == NULL)
    {
        fprintf(stderr, "Error: no memory for list\n");
        return NULL;
    }
    lst->head = NULL;
    lst->list_len = 0;

    return lst;
}

/** list_destroy()
 *  Destructively walk a list, freeing objects as you go, does not free list
 *      object itself, as it may be statically allocated somewhere...
 *  @list -- a pointer to the linked list to destroy
 *  @return -- Nothing
 */
void list_destroy(linked_list *list)
{
    list_node *p = NULL, *tmp = NULL;

    if(list != NULL)
    {
        if(list->head != NULL)
        {
            p = list->head;
            while(p)
            {
                free(p->data);
                tmp = p->next;
                free(p);
                p = tmp;
            }
        }
        free(list);
    }
}

/** list_insert_after()
 *  Create a new node with data of length len and store it after the node
 *      given by *node.
 *  @node -- pointer to a node (presumably already in a list) after which to
 *           insert the new data.
 *  @data -- a pointer to data that will be copied into the new node
 *  @len  -- the length of the data to copy
 *  @return -- a pointer to the new node, or NULL on malloc failure
 */
list_node *list_insert_after(list_node *node, void *data, size_t len)
{
    void *tmp_data = NULL;
    list_node *tmpnode = NULL, *newnode = NULL;

    if(node == NULL)
    {
        fprintf(stderr, "Library error: list_insert_after: node is NULL\n");
        return NULL;
    }

    newnode = malloc(sizeof(list_node));
    tmp_data = malloc(len + 1);
    if(tmp_data == NULL || newnode == NULL)
    {
        fprintf(stderr, "Error: no memory for data or next node\n");
        return NULL;
    }
    memcpy(tmp_data, data, len);
    newnode->data = tmp_data;
    newnode->len = len;

    tmpnode = node->next;
    node->next = newnode;
    newnode->next = tmpnode;

    return newnode;
}

/**
 * list_insert_head()
 *  Insert data at the head of linked list given by *list
 *  @list -- Pointer to list to operate on
 *  @data -- Data to insert in the new node
 *  @len  -- Length of the data to insert
 *  @return -- pointer to the newly created node
 */
list_node *list_insert_head(linked_list *list, void *data, size_t len)
{
    void *tmp_data = NULL;
    list_node *tmpnode = NULL, *newnode = NULL;

    /* Allocate new space for the node and the the new data */
    newnode = malloc(sizeof(list_node));
    if(newnode == NULL)
    {
        fprintf(stderr, "Library Error: list_insert_head -- no memory for the next node");
        return NULL;
    }
    tmp_data = malloc(len + 1);
    if(tmp_data == NULL)
    {
        free(newnode);
        fprintf(stderr, "Library Error: list_insert_head -- no memory for data (%ld) bytes\n", len);
        return NULL;
    }
    memcpy(tmp_data, data, len);
    newnode->data = tmp_data;
    newnode->len = len;

    tmpnode = list->head;
    list->head = newnode;
    newnode->next = tmpnode;

    return newnode;
}

/**
 * list_insert()
 *  Insert data into a list at the head (if *prev is NULL) or after *prev
 *  @list -- Pointer to list to operate on
 *  @prev -- Pointer to node to insert after
 *  @data -- Data to insert in the new node
 *  @len  -- Length of the data to insert
 *  @return -- pointer to the newly created node
 */
list_node *list_insert(linked_list *list, list_node *prev, void *data, size_t len)
{
    if(prev == NULL)
        return list_insert_head(list, data, len);
    else
        return list_insert_after(prev, data, len);
}

/**
 * list_create_node()
 *  Create a new list_node object containing *data of given size len
 *  @data -- Pointer to data to add to new node
 *  @len -- length of *data
 *  @return -- New list_node object or NULL on failure
 */
list_node *list_create_node(void *data, size_t len)
{
    list_node *p = NULL;

    p = malloc(sizeof(list_node));
    if(p != NULL)
    {
        p->next = NULL;
        p->data = data;
        p->len = len;
    }
    else
    {
        fprintf(stderr, "Library error: list_create_node malloc failed");
    }

    return p;
}

/**
 * list_destroy_node()
 *  Free memory associated with given list node
 *
 * @node -- Pointer to list node to free
 */

void list_destroy_node(list_node *node)
{
    if (node->data != NULL)
        free(node->data);
    free(node);
}


/** list_insert_node()
 *  Insert the given node at the head of the given list
 *  @list -- a pointer to a linked list
 *  @newnode -- a pointer to a new node to add to @list
 *  @return -- NULL on error, *new head on success
 */
list_node *list_insert_node(linked_list *list, list_node *newnode)
{
    if(list == NULL || newnode == NULL)
    {
        fprintf(stderr, "Library error: list_insert_node got a NULL argument");
        return NULL;
    }

    newnode->next = list->head->next;
    list->head = newnode;

    return list->head;
}

/** list_delete_next()
 *  Delete the node that comes after the one given in the argument
 *  @node -- a pointer to a node in a linked list
 *  @return -- *node: a pointer to the node, or NULL to indicate a programming
 *                    error (next node doesn't exist)
 */
list_node *list_delete_next(list_node *node)
{
    list_node *tmp;

    if(node->next == NULL)
    {
        fprintf(stderr, "Library error: list_delete_next: node->next = NULL\n");
        return NULL;
    }
    tmp = node->next;
    free(tmp->data);
    node->next = tmp->next;
    free(tmp);
    return node;
}

/** list_delete_head()
 *  Delete the head node of a linked list.
 *  @list -- pointer to linked list to operate on
 *  @return -- a pointer to the new head, or NULL on error
 */
list_node *list_delete_head(linked_list *list)
{
    list_node *oldhead;

    if(list->head != NULL)
    {
        oldhead = list->head;
        list->head = oldhead->next;
        free(oldhead->data);
        free(oldhead);
        return list->head;
    }
    else
    {
        fprintf(stderr, "Library error: list_delete_head: list->head = NULL\n");
        return NULL;
    }
}

/**
 * list_pop_next()
 *  Remove the node after one given from list and return it
 *
 * @node -- Pointer to node who's successor will be removed/returned
 * @return -- A pointer to the node that has been removed
 */
list_node *list_pop_next(list_node *node)
{
    list_node *p, *r;
    assert(node->next != NULL);

    p = node->next->next;
    r = node->next;
    node->next = p;

    return r;
}

/**
 * list_get_index()
 *  Get the node at index (index = 0 is list->head, 1 is head->next, etc...)
 *
 * @list -- Pointer to list
 * @index -- the integer index to retrieve (0 <= index < list_size(list))
 * @return -- A pointer to the node at index (NULL if index > list_size)
 */
list_node *list_get_index(linked_list *list, size_t index)
{
    list_node *p;
    size_t j = 0;

    p = list->head;

    while(j++ < index && (p = p->next))
        ;

    return p;
}

/**
 * list_apply()
 *  Apply the function pointed to by (*fn) to node->data, replacing
 *  data with what is returned by the function
 *
 * @node -- Pointer to node to start at
 * @fn   -- function pointer to function taking old data as argument and
 *          returning a pointer to that data (presumably modified)
 * @return -- A pointer to the next node in the list
 */
inline list_node *list_apply(list_node *node, void *(*fn)(void *))
{
    node->data = (*fn)(node->data);
    return node->next;
}

/**
 * list_apply_each()
 *  Applies function (*fn) to each node's *data object in *list
 *  @list -- linked list
 *  @fn -- Pointer to function taking/returning void* to apply
 *  @return -- NULL on failure, or ptr to list again
 */
linked_list *list_apply_each(linked_list *list, void *(*fn)(void *))
{
    list_node *p;

    if(list==NULL)
    {
        fprintf(stderr, "Library error: list_apply_each passed a NULL list\n");
        return NULL;
    }

    p = list->head;
    while(p)
    {
        list_apply(p, fn);
        p = p->next;
    }
    return list;
}

/**
 * list_reverse()
 *  Reverses a list in place in O(n)
 *  @list -- pointer to the list to reverse
 *  @ret -- The new head or NULL on error
 */
list_node *list_reverse(linked_list *list)
{
    list_node *p = NULL, *q = NULL, *tmp = NULL;

    if(list->head == NULL)
    {
        fprintf(stderr, "Library error: list_reverse cannot reverse an empty list\n");
        return NULL;
    }

    if(list->head->next == NULL)
        return list->head;

    /* q is one step ahead of p, they walk in step turning q->next to point
     * the previous element p, storing where to advance q to in tmp...
     */
    p = list->head;
    q = list->head->next;

    while(q)
    {
        tmp = q->next;
        q->next = p;
        p = q;
        q = tmp;
    }
    list->head->next = NULL;
    list->head = p;
    return list->head;
}

/**
 * list_size()
 *  Walks the list to the end and returns the length
 *  @list -- pointer to the list to measure
 *  @ret -- Nothing
 */
size_t list_size(linked_list *list)
{
    size_t ctr = 0;
    list_node *p = list->head;
    while(p)
    {
        p = p->next;
        ctr++;
    }
    return ctr;
}

/**
 * list_search()
 *  Searches for an item in the list (O(list_size))
 *  @list -- pointer to the list to search in
 *  @compare -- pointer to the data to search for in the list
 *  @search_fn -- pointer to function that takes two args, the first being the
                  data in the list and the second being supplied in *compare,
                  and returns non-zero on a match.
 *  @ret -- index of found item, or -1 on not found
 */
int list_search(linked_list *list, void *compare, int (*search_fn)(void *, void *))
{
    list_node *p = list->head;
    int result = -1, n = 0;

    while(p)
    {
        if(search_fn(p->data, compare))
        {
            result = n;
            break;
        }
    	n++; p = p->next;
    }

    return result;
}

/**
 * list_copy()
 *  Returns a pointer to a copy of the list given
 *  @list -- linked list to copy
 *  @return -- pointer to copy of list
 */
linked_list *list_copy(linked_list *list)
{
    linked_list *newlist = NULL;
    list_node *newnode;
    list_node *p, *q;
    int mem_failure = 0;

    if(list == NULL)
    {
        fprintf(stderr, "Library Error: list_copy passed a NULL list");
        return NULL;
    }

    newlist = list_init();

    if(newlist != NULL)
    {
        if(list->head != NULL)
        {
            p = list->head;
            if(list_insert_head(newlist, p->data, p->len) == NULL)
            {
                fprintf(stderr, "Library Error: list_copy -- malloc failure for new node");
                free(newlist);
                return NULL;
            }
            q = newlist->head;

            while((p = p->next))
            {
                newnode = malloc(sizeof(list_node));
                if(newnode == NULL)
                {
                    mem_failure = 1;
                    break;
                }
                newnode->data = malloc(p->len);
                if(newnode->data == NULL)
                {
                    mem_failure = 1;
                    free(newnode);
                    break;
                }

                newnode->len = p->len;
                newnode->next = NULL;

                memcpy(newnode->data, p->data, p->len);
                q->next = newnode;
                q = q->next;
            }
            /* Clean up  */
            if(mem_failure)
            {
                fprintf(stderr, "Library Error: list_copy -- malloc failure for new node");
                list_destroy(newlist);
                newlist = NULL;
            }

        }
    }

    return newlist;
 }

/**
 * list_join()
 *  Splice the second list onto the tail of the first
 * @first -- List to append to
 * @second -- List to append
 * @return -- First list again
 */
linked_list *list_join(linked_list *first, linked_list *second)
{
    list_node *p;

    assert(second->head != NULL);

    p = first->head;
    while(p->next)
        p = p->next;

    p->next = second->head;

    return first;
}

/**
 * list_join_after()
 *  Splice a second list after a given node
 * @node -- Splice list after this node
 * @joinee -- list to join into the first one after *node
 * @return -- next node
 */
list_node *list_join_after(list_node *node, linked_list *joinee)
{
    list_node *p, *save;

    save = node->next;
    node->next = joinee->head;
    p = joinee->head;
    while(p->next)
        p = p->next;
    p->next = save;

    return(node->next);
}

/**
 * list_swap_next()
 *  Swap the nodes that follow the two nodes given here (p->next and q->next
 *  are swapped).
 *  @p, @q -- the nodes whose next node will be swapped
 *  @ret -- One of the swapped nodes or NULL on error
 */
list_node *list_swap_next(list_node *p, list_node *q)
{
    list_node *tmp;

    if(q->next == NULL || p->next == NULL)
    {
        fprintf(stderr, "Library error: cannot swap nodes past end of list\n");
        return NULL;
    }

    tmp = q->next;
    q->next = p->next;
    p->next = tmp;

    tmp = q->next->next;
    q->next->next = p->next->next;
    p->next->next = tmp;

    return q;
}

/**
 * list_swap_head()
 *  Swap the head node of *list with *p
 *  @list -- pointer to the list which ->head should be swapped
 *  @p -- the list node whose ->next will be swapped with the head
 *  @ret -- New head or NULL on error
 */
list_node *list_swap_head(linked_list *list, list_node *p)
{
    list_node *tmp;

    if(p->next == NULL)
    {
        fprintf(stderr, "Library error: list_swap_head -- p->next is NULL");
        return NULL;
    }

    tmp = list->head;
    list->head = p->next;
    p->next = tmp;

    tmp = list->head->next;
    list->head->next = p->next->next;
    p->next->next = tmp;

    return list->head;
}

/**
 * list_shuffle()
 *  Shuffle a list in-place, seeding RNG with the current time-microsecond
 *
 *  @list -- The list to operate on
 *
 * FIXME: This doesn't work well on small lists, and is likely not a proper
 *        random shuffle, with bias towards something or another
 */
void list_shuffle(linked_list *list)
{
    int len = list_size(list);
    int pos = 1, to_go, i;
    list_node *p, *q;
    struct timeval t;

    if(len < 2)
        return;

    gettimeofday(&t, NULL);
    srand48(t.tv_sec ^ t.tv_usec);

    q = list->head;
    for(i=0; i< lrand48() % (len - 1); i++)
        q = q->next;
    list_swap_head(list, q);
    p = list->head;

    while(p->next)
    {
        to_go = lrand48() % (len - pos);
        q = p;
        for(i=0; i < to_go; i++)
            q = q->next;

        list_swap_next(p, q);
        p = p->next;
        pos++;
    }
}
