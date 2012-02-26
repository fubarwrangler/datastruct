#include <stdio.h>
#include <string.h>

#include "hash.h"


void print_hash(hash_table *h)
{
	int i;

	printf("n: %d, hash_fn = %p, buckets at %p\n", h->n_buckets, h->hash_fn, h->buckets);
	for(i=0; i<h->n_buckets; i++)	{
		printf("Bucket %d: %p (%p)\n", i, h->buckets[i], &h->buckets[i]);
	}
}

int main(int argc, char const *argv[])
{
	hash_table *hash;

	hash = hash_init(NULL);

	print_hash(hash);

	hash_destroy(hash);

	return 0;
}

