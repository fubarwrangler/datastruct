#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash.h"


hash_table *hash_init(hash_fn_t hash_fn, size_t initial_size)
{
	hash_table *h = malloc(sizeof(hash_table));

	if(h != NULL)	{
		/* Did we supply a hash function? */
		h->hash_fn = (hash_fn == NULL) ? &default_hash_fn : hash_fn;
		/* How about an initial size */
		h->size = (initial_size == 0) ? INIT_HASH_TBL_SIZE : initial_size;
		h->nelm = 0;
		h->flags = 0;
		h->g_trigger = 1.0;
		h->g_factor = 2.0;
		h->buckets = calloc(h->size, sizeof(bucket_data *));
		if(h->buckets != NULL)	{
			size_t i;
			for(i = 0; i < h->size; i++)
				h->buckets[i] = NULL;
			return h;
		} else {
			free(h);
		}
	}
	return NULL;
}

void hash_destroy(hash_table *h)
{
	/* Walk each bucket's list freeing as we go */
	if(h!=NULL)	{
		if(h->buckets != NULL)	{
			bucket_data *b, *nb;
			int i;

			for(i = 0; i < h->size; i++)	{
				b = h->buckets[i];
				while(b != NULL)	{
					nb = b->next;
					free(b->key);
					if(h->flags & HASH_AUTOFREE_)
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

	/* Will this one push us over the top if autogrow is on? */
	if(h->flags & HASH_AUTOGROW_)	{
		float load = (float)h->nelm / (float)h->size;
		if(load > h->g_trigger)	{
			size_t newsize = ceil((float)h->size * h->g_factor);
			/* Grow the hash table */
			if(hash_resize(h, newsize) != 0)
				return 1;
		}
	}

	b = h->buckets[idx];

	/* Walk the bucket list to see if it exists already, if so silently
	 * update, freeing if autofree set
	 */
	while(b != NULL)	{
		if(strcmp(b->key, key) == 0)	{
			if(h->flags & HASH_AUTOFREE_)
				free(b->data);
			b->data = data;
			return 0;
		}
		pb = b;
		b = b->next;
	}

	/* If not in the list, append to the end of the list */
	if((b = malloc(sizeof(bucket_data))) == NULL)
		return 1;

	if((b->key = strdup(key)) == NULL)	{
		free(b);
		return 1;
	}

	b->data = data;
	b->next = NULL;

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

			if(h->flags & HASH_AUTOFREE_)
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
	unsigned int i;

	/* New ptr array for buckets, hash each old val into this new array */
	if((newbuckets = calloc(newsize, sizeof(bucket_data *))) == NULL)
		return 1;
	for(i = 0; i < h->size; i++)	{
		b = h->buckets[i];
		/* For each old bucket item, insert into correct new bucket */
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
	/* Replace old with new */
	free(h->buckets);
	h->buckets = newbuckets;
	h->size = newsize;

	return 0;
}


