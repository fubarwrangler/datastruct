#ifndef HASH_H__
#define HASH_H__

#include <stddef.h>

#define INIT_HASH_TBL_SIZE 16


typedef unsigned int (*hash_fn_t)(const char *);

typedef struct _bucket_data
{
	char *key;
	void *data;
	struct _bucket_data *next;

} bucket_data;

typedef struct _hash_table {
	size_t size;
	size_t nelm;
	bucket_data **buckets;
	hash_fn_t hash_fn;
} hash_table;


unsigned int default_hash_fn(const char *key)
{
    unsigned int hash = 0;
	
    while(*key)
    {
        hash += *key++;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}


/**
 * hash_init() -- initalize a new hash table with hash function @hash_fn
 *
 * @hash_fn: the hash function to use, or NULL to use the default
 *
 * Returns: new empty hash table of INIT_HASH_TBL_SIZE size, NULL on failure
 */
hash_table *hash_init(hash_fn_t hash_fn);


/**
 * hash_destroy() -- free all memory associated with hash table
 *
 * @h: hash table to free
 */
void hash_destroy(hash_table *h);


int hash_insert(hash_table* h, const char* key, void* data);


#endif /* HASH_H__ */