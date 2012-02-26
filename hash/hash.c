#include <stdio.h>
#include <stdlib.h>

#include "hash.h"


hash_table *hash_init(hash_fn_t hash_fn)
{
	hash_table *h = malloc(sizeof(hash_table));
	int i, j;

	if(h != NULL)	{
		
		h->hash_fn = (hash_fn == NULL) ? &default_hash_fn : hash_fn;
		h->n_buckets = INIT_HASH_TBL_SIZE;
		h->buckets = malloc(h->n_buckets * sizeof(bucket_data *));
		if(h->buckets != NULL) {
			for(i = 0; i < h->n_buckets; i++)
				h->buckets[i] = NULL;
			return h;
		} else {
			free(h);
		}
	}
	return NULL;
}


/* XXX: NOT DONE -- must free buckets too */
void hash_destroy(hash_table *h)
{
	if(h!=NULL)	{
		if(h->buckets != NULL)
			free(h->buckets);
		free(h);
	}
}


int hash_insert(hash_table *h,
				char *key, size_t k_len,
				char *data, size_t d_len)
{
	return 0; /* here */
}