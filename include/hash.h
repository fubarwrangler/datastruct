#ifndef HASH_H__
#define HASH_H__

#include <stddef.h>

#define INIT_HASH_TBL_SIZE 10

/* Hash function type -- maps strings to unsigned ints */
typedef unsigned int (*hash_fn_t)(const char *);

typedef struct _bucket_data
{
	char *key;
	void *data;
	struct _bucket_data *next;

} bucket_data;

typedef struct _hash_table {
	size_t size;	/* Number of buckets */
	size_t nelm;	/* Number of elements in hash table */
	int autofree;	/* Bool flag if we call free() on bucket->data */
	bucket_data **buckets;
	hash_fn_t hash_fn;
} hash_table;

/**
 * This is the hash to use if no user-supplied one is provided, it is an
 * implementation of Jenkins's hash -- a good general purpose hash function
 * for typical keys:
 *
 * SOURCE: Jenkins, Bob (September 1997). "Hash functions". Dr. Dobbs Journal.
 */
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

inline void hash_set_autofree(hash_table *h)
{
	h->autofree = 1;
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

/**
 * hash_insert() -- insert a key/data pair into a hash table
 *  @h: hash table to use
 *  @key: the string to use as a key
 *  @data: pointer to data to store associated with key
 *
 * Returns: 0 on success, non-zero on failure (memory error)
 */
int hash_insert(hash_table* h, const char* key, void* data);

/**
 * hash_insert_string() -- like insert, but use a copy of char *val
 *	@@ -- same as hash_insert
 *  @val -- a string that will be dup'd before inserting
 *
 * WARNING: make sure to use freedata = 1 when destroying a hash table created
 *          by using this function.
 *
 * Returns: 0 on success, 1 on failure
 */
int hash_insert_string(hash_table *h, const char *key, char *val);

/**
 * hash_get() -- search for key in a hash table
 *  @h: hash table to look in
 *  @key: the string to search for
 *
 * Returns: the data corresponding to @key, or NULL if not present
 */
void *hash_get(hash_table *h, const char *key);

/**
 * hash_delete() -- remove key from hash table
 *  @h: hash table to delete from
 *  @key: key to remove
 *
 * Returns: 0 on successful delete, 1 on key-not-found
 */
int hash_delete(hash_table *h, const char *key);


/**
 * hash_resize() -- resize a hash table, rehashing all keys into new buckets
 *  @h: hash table
 *  @newsize: the new number of buckets
 *
 * Returns: 0 on success, 1 on error (memory)
 */
int hash_resize(hash_table *h, size_t newsize);


#endif /* HASH_H__ */
