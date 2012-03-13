#ifndef TREE_H_
#define TREE_H_

typedef int (*bintree_cmp)(void *, void *);

struct btnode {
	struct btnode *left;
	struct btnode *right;
	void *data;
};

typedef struct _binary_tree {
	struct btnode *root;
	bintree_cmp cmp_fn;
} binary_tree;

binary_tree *init_bintree(bintree_cmp cmp_fn);

void destroy_bintree(binary_tree *bt);

void *bintree_search(binary_tree *bt, void *data);

int bintree_insert(binary_tree *bt, void *data);

int bintree_delete(binary_tree *bt, void *value);

#endif /* TREE_H_ */
