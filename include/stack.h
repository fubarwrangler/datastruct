#ifndef _STACK_H
#define _STACK_H

#include "sllist.h"

typedef list_node stack_item;
typedef linked_list stack;


#define stack_init() list_init()
#define stack_destroy(x) list_destroy(x)
#define stack_push(s, p, l) list_insert_head(s, p, l)
#define stack_push_item(s, i) list_insert_node(s, i)
#define stack_pop(l) list_pop_head(l)
#define stack_copy(l) list_copy(l)
#define stack_peek(s) (s->head == NULL ? NULL: s->head->data)
#define stack_peek_item(s) s->head
#define stack_destroy_item(p) list_destroy_node(p)
#define stack_size(stk) list_size(stk)
#define stack_empty(s) (s->head == NULL ? 1 : 0)

#endif
