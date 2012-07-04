#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

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
			free(p);
			p = q;
		}
		free(list);
		list = NULL;
	}
}

/* This could be made 2x faster, but whatever */
void dllist_destroy_callback(dllist *list, dllist_map_fn_t fn)
{
	dllist_apply_each(list, fn);
	dllist_destroy(list);
}

dlnode *dllist_insert(dllist *list, void *data)
{
	dlnode *p, *q;

	assert(list != NULL);

	p = malloc(sizeof(dlnode));
	if(p != NULL)
	{
		p->prev = NULL;

		p->data = data;
		
		q = list->head;
		if(q != NULL)
			q->prev = p;
		else
			list->tail = p;
		
		list->head = p;
		p->next = q;
	}
	else
		fprintf(stderr, "Library Error: dllist_insert--No memory for new node");

	return p;
}

dlnode *dllist_append(dllist* list, void* data)
{
	dlnode *p, *q;

	p = malloc(sizeof(dlnode));
	if(p != NULL)
	{
		p->prev = NULL;

		p->data = data;
		q = list->tail;
		if(q != NULL)
			q->next = p;
		else
			list->head = p;
		list->tail = p;
		p->prev = q;
	}
	else
		fprintf(stderr, "Library Error: dllist_append--No memory for new node");

	return p;
}

/* dllist_insert_after() only for nodes in the middle of the list,
 * because, otherwise we couldn't update the head/tail pointers in the
 * containing structure
 */
dlnode *dllist_insert_after(dlnode* node, void* data)
{
	dlnode *p = NULL, *q = NULL;

	assert(node != NULL);

	if(node->next == NULL)	{
		fputs("dllist_insert_after: cannot insert after tail", stderr);
		return NULL;
	}

	p = malloc(sizeof (dlnode));

	if(p == NULL)
		fprintf(stderr, "dllist_insert_after: *node is NULL or no Memory\n");
	else	{
		p->data = data;

		q = node->next;

		node->next = p;
		p->prev = node;
		p->next = q;
	}
	return p;
}


void dllist_swap(dllist *list, dlnode *n1, dlnode *n2)
{
	dlnode *p, *q;

	assert(list != NULL && n1 != NULL && n2 != NULL);

	/* Nodes' next pointers, if we get null we know to update list->tail */
	p = n1->next;
	if(p != NULL)
		p->prev = n2;
	else
		list->tail = n2;

	n1->next = n2->next;

	q = n2->next;
	if(q != NULL)
		q->prev = n1;
	else
		list->tail = n1;

	n2->next = p;

	/* Nodes' previous pointers, checking to update list->head as well */
	p = n1->prev;
	if(p != NULL)
		p->next = n2;
	else
		list->head = n2;

	n1->prev = n2->prev;

	q = n2->prev;
	if(q != NULL)
		q->next = n1;
	else
		list->head = n1;

	n2->prev = p;
}

size_t dllist_size(dllist *list)
{
	size_t ctr = 0;
	dlnode *p = list->head;;

	if(p != NULL)
	{
		while((p = p->next))
			ctr++;
	}
	return ctr;
}

dlnode *dllist_get_index(dllist *list, size_t idx)
{
	dlnode *p;
	size_t ctr = 0;

	assert(list != NULL);

	p = list->head;
	while(p && ctr++ < idx)
		p = p->next;
	return p;
}

void *dllist_delete(dllist *list, dlnode *node)
{
	void *dataptr = NULL;

	assert(list != NULL && node != NULL);

	dataptr = node->data;

	if(node == list->head)	{
		list->head = node->next;
		node->next->prev = NULL;
	} else if(node == list->tail)	{
		list->tail = node->prev;
		node->prev->next = NULL;
	} else	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node);
	return dataptr;
}

void dllist_apply_each(dllist *list, dllist_map_fn_t fn)
{
	dlnode *p = list->head;

	while(p != NULL)
	{
		fn(p->data);
		p = p->next;
	}
}

dllist *dllist_copy(dllist *list)
{
	dlnode *p;
	dllist *newlist;

	newlist = dllist_init();
	if(newlist != NULL)
	{
		for(p = list->head; p != NULL; p = p->next)
		{
			if(dllist_append(newlist, p->data) == NULL)
			{
				dllist_destroy(newlist);
				break;
			}
		}
	}

	return newlist;
}

dllist *dllist_join(dllist *first, dllist *second)
{
	first->tail->next = second->head;
	second->head->prev = first->tail;
	first->tail = second->tail;
	second->head = NULL;
	second->tail = NULL;
	return first;
}

void dllist_reverse(dllist *list)
{
	dlnode *tmp;
	dlnode *p = list->head;

	/* p points at orig. head */
	list->head = list->tail;
	list->tail = p;

	/* assign to p->prev here because it has already been swapped! */
	for(; p != NULL; p = p->prev)
	{
		tmp = p->next;
		p->next = p->prev;
		p->prev = tmp;
	}
}


dlnode *dllist_search(dllist *list, void *value, dllist_cmp_fn_t cmp)
{
	dlnode *p;

	for(p = list->head; p != NULL && !cmp(value, p->data); p = p->next)
		;

	return p;
}


long dllist_find_index(dllist *list, void *value, dllist_cmp_fn_t cmp)
{
	dlnode *p = list->head;
	long i = 0, result = -1;

	while(p != NULL && result < 0)
	{
		if(cmp(value, p->data))
			result = i;
		i++; p = p->next;
	}
	return result;
}
