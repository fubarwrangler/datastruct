#include <stdio.h>
#include <string.h>

#include "hash.h"


void print_hash(hash_table *h)
{
	int i;

	printf("%d hashed into %d buckets, hash_fn = %p, buckets at %p\n",
		    h->nelm, h->size, h->hash_fn, h->buckets);
	for(i=0; i<h->size; i++)	{
		printf("Bucket %d: %p (%p)", i, h->buckets[i], &h->buckets[i]);
		if(h->buckets[i])	{
			bucket_data *b = h->buckets[i];
			while(b) {
				printf("\n  %s => %s (next %p)", b->key, (char *)b->data, b->next);
				b = b->next;
			}
		}
		putchar('\n');
	}
}

int main(int argc, char const *argv[])
{
	hash_table *hash;

	hash = hash_init(NULL);

	hash_insert(hash, "California", "Sacremento");
	hash_insert(hash, "Virginia", "Richmond");
	hash_insert(hash, "Lol", "Not me");
	hash_insert(hash, "What", "CRASH!");

	
	

	print_hash(hash);

	hash_destroy(hash);

	return 0;
}

