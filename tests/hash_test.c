#include <stdio.h>
#include <stdlib.h>
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
			int j = 0;
			bucket_data *b = h->buckets[i];
			while(b) {
				j++;
				if(j < 4 || b->next == NULL)
					printf("\n  %s => (%p) (%s) (next %p)", b->key, b->data, (char *)b->data, b->next);
				else if(j == 4 && b->next != NULL)
					printf("\n  ...");
				b = b->next;
			}
			if(j > 4)
				printf("\n%d skipped", j - 4);
		}
		putchar('\n');
	}
}

char *strduprev(char *str)
{
	char *p;
	int n = strlen(str), i = 0;

	p = malloc(n + 1);
	while(i < n)	{
		p[i] = str[n - i - 1];
		i++;
	}
	p[i] = '\0';

	return p;
}


void fill_words(hash_table *h, char *file)
{
	FILE *fp = fopen(file, "r");
	char buf[1024];
	if(fp == NULL)	{
		printf("Cannot open %s\n", file);
		exit(1);
	}

	while(fgets(buf, 1024, fp) != NULL)	{
		buf[strlen(buf) - 1] = '\0';
		hash_insert(h, buf, strduprev(buf));
	}
	fclose(fp);
}

int main(int argc, char const *argv[])
{
	hash_table *hash;

	hash = hash_init(NULL);
	hash_set_autofree(hash);

	hash_insert_string(hash, "California", "Sacremento");
	hash_insert_string(hash, "Virginia", "Richmond");
	hash_insert_string(hash, "Lol", "Not me");
	hash_insert_string(hash, "What", "CRASH!");


	printf("1. %s\n", hash_get(hash, "California"));
	printf("2. %s\n", hash_get(hash, "Wut"));


	fill_words(hash, "data/words.txt");
	hash_insert_string(hash, "woodland", "creatures");
	hash_insert_string(hash, "look", "overwritten");
	print_hash(hash);

	hash_resize(hash, 4);

	print_hash(hash);

	hash_resize(hash, 75);

	print_hash(hash);

	hash_resize(hash, 16);

	print_hash(hash);

	
	hash_destroy(hash);
	return 0;
}

