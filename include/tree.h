#ifndef TREE_H_
#define TREE_H_

typedef int (*bintree_cmp)(void *, void *);

struct btnode {
	struct btnode *left;
	struct btnode *right;
	void *data;
};

struct binary_tree {
	struct btnode *root;
	bintree_cmp cmp_fn;
};

struct binary_tree *init_bintree(bintree_cmp cmp_fn);

void destroy_bintree(struct binary_tree *bt);

void *bintree_search(struct binary_tree *bt, void *data);

int bintree_insert(struct binary_tree *bt, void *data);

#endif /* TREE_H_ */
