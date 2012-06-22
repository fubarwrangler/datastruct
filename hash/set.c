#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "set.h"


set *set_init(size_t initial_size)
{
	set *s = malloc(sizeof(set));

	s->ht = hash_init(NULL, (initial_size == 0) ? 10 : initial_size);
	s->_shared_data = &s;
	hash_set_autogrow(s->ht, 0.8, 2.0);

	return s;
}

void set_destroy(set *s)
{
	hash_destroy(s->ht);
	free(s);
}

int set_add(set *s, const char *key)
{
	return hash_insert(s->ht, key, &s->_shared_data);
}

int set_ismember(set *s, const char *key)
{
	return (hash_get(s->ht, key) != NULL);
}

int set_remove(set *s, const char *key)
{
	return hash_delete(s->ht, key);
}

size_t set_size(set *s)
{
	return s->ht->nelm;
}




