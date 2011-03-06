#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"

/** list_init()
 *  Allocates a new linked list and returns a pointer to it, will possibly
 *  fail on memory allocation error, returning NULL instead.
 *  @arg -- None
 *  @return -- An allocated link list object with a null head node
 */
linked_list *list_init(void)
{
    linked_list *lst = NULL;
    lst = malloc(sizeof(linked_list));
    if(lst == NULL)
    {
        printf("Error: no memory for list\n");
        return NULL;
    }
    lst->head = NULL;

    return lst;
}

/** list_destroy()
 *  Destructively walk a list, freeing objects as you go
 *  @list -- a pointer to the linked list to destroy
 *  @return -- Nothing
 */
void list_destroy(linked_list *list)
{
    list_node *p = NULL, *tmp = NULL;

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

    newnode = malloc(sizeof(list_node));
    tmp_data = malloc(len + 1);
    if(tmp_data == NULL || newnode == NULL)
    {
        fprintf(stderr, "Error: no memory for data or next node\n");
        return NULL;
    }
    memcpy(tmp_data, data, len);
    newnode->data = tmp_data;
    if(node == NULL)
    {
        printf("Library error: list_insert_after: node is NULL\n");
        return NULL;
    }
    else
    {
        tmpnode = node->next;
        node->next = newnode;
        newnode->next = tmpnode;
    }
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
        fprintf(stderr, "Error: no memory for the next node");
        return NULL;
    }
    tmp_data = malloc(len + 1);
    if(tmp_data == NULL)
    {
        free(newnode);
        fprintf(stderr, "Error: no memory for data (%d) bytes\n", len);
        return NULL;
    }
    memcpy(tmp_data, data, len);
    newnode->data = tmp_data;

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
 *  @return -- *list: a pointer to the list, or NULL to indicate a programming
 *                    error (head node doesn't exist)
 */
linked_list *list_delete_head(linked_list *list)
{
    list_node *oldhead;
    if(list->head != NULL)
    {
        oldhead = list->head;
        list->head = oldhead->next;
        free(oldhead->data);
        free(oldhead);
        return list;
    }
    else
    {
        fprintf(stderr, "Library error: list_delete_head: list->head = NULL\n");
        return NULL;
    }

}

/**
 * list_apply()
 *  Apply the function pointed to by (*fn) to node->data
 *
 * @node -- Pointer to node to start at
 * @fn   -- function pointer to function taking old data as argument and
 *          returning a pointer to that data (presumably modified)
 * @return -- A pointer to the next node in the list
 */
list_node *list_apply(list_node *node, void *(*fn)(void *))
{
    node->data = (*fn)(node->data);
    return node->next;
}

/**
 * list_reverse()
 *  Reverses a list in place in O(n)
 *  @list -- pointer to the list to reverse
 *  @ret -- Nothing
 */
void list_reverse(linked_list *list)
{
    list_node *p = NULL, *q = NULL, *tmp = NULL;

    if(list->head == NULL)
    {
        printf("Library error: list_reverse -- cannot reverse an empty list\n");
        return;
    }
    if(list->head->next == NULL)
    {
        printf("Library warning: list_reverse -- trivial to reverse one-element list\n");
        return;
    }

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
}

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

void list_swap(list_node *p, list_node *q)
{
    list_node *tmp, *tmp1;

    if(q->next == NULL || p->next == NULL)
    {
        fprintf(stderr, "Library error: cannot swap nodes past end of list\n");
        return;
    }

    tmp = q->next->next;
    q->next->next = p->next->next;
    p->next->next = tmp;

    tmp = q->next;
    q->next = p->next;
    p->next = tmp;
}


void list_shuffle(linked_list *list)
{
    int len = list_size(list);
    int pos = 0, to_go, i;
    list_node *p, *q, *tmp1, *tmp;

    srand48(69);
    p = list->head;
    while(p)
    {
        to_go = (lrand48() % (len - pos - 1)) + 1;
        q = p;
        for(i=0; i<to_go; i++)
            q = q->next;

        list_swap(p, q);


        p = p->next;

        pos++;
        printf("************\n");
        list_printer(list);
    }


    return;
}
