#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "set.h"


set *set_init(size_t initial_size)
{
	set *s = malloc(sizeof(set));

	s->ht = hash_init(NULL, (initial_size == 0) ? 10 : initial_size);
	hash_set_autogrow(s->ht, 0.8, 2.0);

	return s;
}

void set_destroy(set *s)
{
	hash_destroy(s->ht);
	free(s);
}

set *set_copy(set *s)
{
	set_iter i;
	char *p;
	set *new_set = set_init(set_size(s));

	if(new_set == NULL)
		return NULL;

	set_iter_init(s, &i);
	while((p = set_iterate(s, &i)) != NULL)	{
		set_add(new_set, p);
	}
	return new_set;
}

void set_iter_init(set *s, set_iter *iter)
{
	hash_iter_init(s->ht, iter);
}

char *set_iterate(set *s, set_iter *state)
{
	char *str;
	void *dummy;

	return (hash_iterate(s->ht, (hash_iter *)state, &str, &dummy) == 1) ?
			str : NULL; /* true : false */
}

int set_add(set *s, const char *key)
{
	/* It doesn't matter what we point at for the value */
	return hash_insert(s->ht, key, &s);
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

set *set_or(set *s1, set *s2)
{
	set_iter itr;
	char *str;
	set *s = set_copy(s1);

	set_iter_init(s2, &itr);

	while((str = set_iterate(s2, &itr)) != NULL)
		set_add(s, str);

	return s;
}


set *set_and(set *s1, set *s2)
{
	set_iter itr;
	char *str;
	set *s = set_init((set_size(s1) + set_size(s2)) / 2);

	for(set_iter_init(s1, &itr); (str = set_iterate(s1, &itr)) != NULL; )	{
		if(set_ismember(s2, str))
			set_add(s, str);
	}

	for(set_iter_init(s2, &itr); (str = set_iterate(s2, &itr)) != NULL; )	{
		if(set_ismember(s1, str))
			set_add(s, str);
	}

	return s;
}



