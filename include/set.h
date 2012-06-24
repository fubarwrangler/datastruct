#ifndef SET_H__
#define SET_H__

#include "hash.h"

typedef struct _set
{
	hash_table *ht;
} set;

typedef hash_iter set_iter;

/* Creation, destruction, and copying */
set *set_init(size_t initial_size);
void set_destroy(set *s);
set *set_copy(set *s);

/* Basic modification and membership testing */
int set_add(set *s, const char *key);
int set_remove(set *s, const char *key);
int set_ismember(set *s, const char *key);

size_t set_size(set *s);

void set_iter_init(set *s, set_iter *iter);
char *set_iterate(set *s, set_iter *state);

/* returns elements common to both sets */
set *set_intersect(set *s1, set *s2);

/* returns all elements from both sets */
set *set_union(set *s1, set *s2);

/* elements unique to each set */
set *set_xor(set *s1, set *s2);

/* elements in s1 that are not in s2 */
set *set_diff(set *s1, set *s2);

/* Tests if s2 is a subset of s1 */
int set_subset(set *s1, set *s2);

#endif /* SET_H__ */