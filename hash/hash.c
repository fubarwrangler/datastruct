#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"


hash_table *hash_init(hash_fn_t hash_fn)
{
	hash_table *h = malloc(sizeof(hash_table));

	if(h != NULL)	{
		/* Did we supply a hash function? */
		h->hash_fn = (hash_fn == NULL) ? &default_hash_fn : hash_fn;
		/* TODO: make this a parameter? */
		h->size = INIT_HASH_TBL_SIZE;
		h->nelm = 0;
		h->autofree = 0;
		h->buckets = calloc(h->size, sizeof(bucket_data *));
		if(h->buckets != NULL)
			return h;
		else
			free(h);
	}
	return NULL;
}


/* XXX: NOT DONE -- must free buckets too */
void hash_destroy(hash_table *h)
{
	if(h!=NULL)	{
		if(h->buckets != NULL)	{
			bucket_data *b, *nb;
			int i;

			for(i = 0; i < h->size; i++)	{
				b = h->buckets[i];
				while(b != NULL)	{
					nb = b->next;
					free(b->key);
					if(h->autofree)
						free(b->data);
					free(b);
					b = nb;
				}
			}
			free(h->buckets);
		}
		free(h);
	}
}

int hash_insert(hash_table *h, const char *key, void *data)
{
	bucket_data *b, *pb = NULL;
	unsigned int idx = h->hash_fn(key) % h->size;

	b = h->buckets[idx];

	while(b != NULL)	{
		if(strcmp(b->key, key) == 0)	{
			if(h->autofree)
				free(b->data);
			b->data = data;
			return 0;
		}
		pb = b;
		b = b->next;
	}

	if((b = malloc(sizeof(bucket_data))) == NULL)
		return 1;

	if((b->key = strdup(key)) == NULL)	{
		free(b);
		return 1;
	}

	b->data = data;

	if(pb != NULL)
		pb->next = b;
	else
		h->buckets[idx] = b;
	h->nelm++;

	return 0;
}


int hash_insert_string(hash_table *h, const char *key, char *val)
{
	char *n;

	if((n = strdup(val)) == NULL)
		return 1;

	if(hash_insert(h, key, n) != 0)	{
		free(n);
		return 1;
	}

	return 0;
}


void *hash_get(hash_table *h, const char *key)
{
	bucket_data *b = h->buckets[h->hash_fn(key) % h->size];

	while(b != NULL)	{
		if(strcmp(b->key, key) == 0)
			return b->data;
		b = b->next;
	}
	return NULL;
}

int hash_delete(hash_table *h, const char *key)
{
	unsigned int idx = h->hash_fn(key) % h->size;
	bucket_data *b = h->buckets[idx];
	bucket_data *pb = NULL;

	while(b != NULL)	{
		if(strcmp(b->key, key) == 0)	{
			if(pb == NULL)
				h->buckets[idx] = b->next;
			else
				pb->next = b->next;

			if(h->autofree)
				free(b->data);
			free(b->key);
			free(b);
			h->nelm--;
			return 0;
		}
		pb = b;
		b = b->next;
	}
	return 1;
}


int hash_resize(hash_table *h, size_t newsize)
{
	bucket_data **newbuckets;
	bucket_data *b, *target, *prev, *next;
	int i, j;

	if((newbuckets = calloc(newsize, sizeof(bucket_data *))) == NULL)
		return 1;
	for(i = 0; i < h->size; i++)	{
		b = h->buckets[i];
		while(b)	{
			unsigned int idx = h->hash_fn(b->key) % newsize;
			next = b->next;

			if(newbuckets[idx] == NULL)	{
				newbuckets[idx] = b;
				b->next = NULL;
			} else {
				target = newbuckets[idx];
				while(target) {
					prev = target;
					target = target->next;
				}
				prev->next = b;
				b->next = NULL;
			}

			b = next;
		}
	}
	free(h->buckets);
	h->buckets = newbuckets;
	h->size = newsize;

	return 0;
}


