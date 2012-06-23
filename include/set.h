#ifndef SET_H__
#define SET_H__

#include "hash.h"

typedef struct _set
{
	hash_table *ht;
} set;

typedef hash_iter set_iter;

set *set_init(size_t initial_size);
void set_destroy(set *s);

int set_add(set *s, const char *key);
int set_remove(set *s, const char *key);
int set_ismember(set *s, const char *key);
size_t set_size(set *s);

void set_iter_init(set *s, set_iter *iter);
char *set_iterate(set *s, set_iter *state);

set *set_copy(set *s);

/* Names may not match logic? */
set *set_and(set *s1, set *s2);
set *set_or(set *s1, set *s2);

#endif /* SET_H__ */