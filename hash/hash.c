#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"


hash_table *hash_init(hash_fn_t hash_fn)
{
	int i, j;
	hash_table *h = malloc(sizeof(hash_table));

	if(h != NULL)	{
		
		h->hash_fn = (hash_fn == NULL) ? &default_hash_fn : hash_fn;
		h->size = INIT_HASH_TBL_SIZE;
		h->buckets = malloc(h->size * sizeof(bucket_data *));
		h->nelm = 0;
		if(h->buckets != NULL) {
			for(i = 0; i < h->size; i++)
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
		if(h->buckets != NULL)	{
			bucket_data *b, *nb;
			int i;
			
			for(i = 0; i < h->size; i++)	{
				b = h->buckets[i];
				while(b != NULL)	{
					nb = b->next;
					free(b->key);
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
	printf("New in chain at %d\n", idx);

	
	while(b != NULL)	{
		if(strcmp(b->key, key) == 0)	{
			b->data = data;
			return 0;
		}
		pb = b;
		b = b->next;
	}

	if((b = malloc(sizeof(bucket_data))) == NULL)
		return 1;
	
	if((b->key = strdup(key)) == NULL)
		return 1;
	
	b->data = data;
	if(pb != NULL)
		pb->next = b;
	else
		h->buckets[idx] = b;
	h->nelm++;

	return 0;
}