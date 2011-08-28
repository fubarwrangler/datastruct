#ifndef _QUEUE_H_
#define _QUEUE_H_



#include "dllist.h"

typedef dlnode qitem;
typedef dllist queue;


#define queue_init() dllist_init()
#define queue_destroy(x) dllist_destroy(x)
#define queue_put(q, d, l) dllist_append(q, d, l)
#define queue_get(q)

#define queue_copy(q) dllist_copy(q)
#define queue_peek(q) q->head
#define queue_length(q) dlist_size(q)
#define queue_del(item) dllist_destroy_item(item)
#define queue_empty(q) (s->head == NULL ? 1 : 0)


#endif // _QUEUE_H_
