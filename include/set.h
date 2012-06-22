#ifndef SET_H__
#define SET_H__

#include "hash.h"

typedef struct _set
{
	hash_table *ht;

	/* All value pointers in hash table point at address of this to
	 * differentiate NULL from not present in the hash table.
// 	 */
	void *_shared_data;
} set;

set *set_init(size_t initial_size);
void set_destroy(set *s);

int set_add(set *s, const char *key);
int set_remove(set *s, const char *key);
int set_ismember(set *s, const char *key);
size_t set_size(set *s);

#endif /* SET_H__ */