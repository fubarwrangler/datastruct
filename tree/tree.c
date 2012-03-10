#include <stdio.h>
#include <stdlib.h>

#include "tree.h"


struct binary_tree *init_bintree(bintree_cmp cmp_fn)
{
	struct binary_tree *b = malloc(sizeof(struct binary_tree));
	if(b != NULL)	{
		b->cmp_fn = cmp_fn;
		b->root = NULL;
	}
	return b;
}

static void freetree(struct btnode *p)
{
	if(p == NULL)
		return;
	freetree(p->left);
	freetree(p->right);
	free(p);
}

void destroy_bintree(struct binary_tree *bt)
{
	struct btnode *n = bt->root;
	freetree(bt->root);
	//free(bt->root);
	free(bt);
}

static struct btnode **btn_srch(struct binary_tree *bt, void *data)
{
	struct btnode **n = &(bt->root);
	int res;

	while(*n != NULL)	{
		res = bt->cmp_fn(data, (*n)->data);
		if(res < 0) {
			n = &(*n)->left;
		} else if (res > 0)	{
			n = &(*n)->right;
		} else {
			break;
		}
	}
	return n;
}

void *bintree_search(struct binary_tree *bt, void *data)
{
	struct btnode **n = btn_srch(bt, data);
	if(*n != NULL)
		return (*n)->data;
	else
		return *n;
}

int bintree_insert(struct binary_tree *bt, void *data)
{
	struct btnode **n = btn_srch(bt, data);

	/* Find where we want to go and allocate space for node */
	if(*n == NULL)	{
		*n = malloc(sizeof(struct btnode));
		if(*n == NULL)
			return -1;
		(*n)->left = (*n)->right = NULL;
		(*n)->data = data;
		return 0;
	}
	return 1;
}

int bintree_delete(struct binary_tree *bt, void *value)
{
	struct btnode *p, *q;
	struct btnode **node = btn_srch(bt, value);

	if(*node == NULL)
		return 1;

	/* Store current place for future freeing */
	p = *node;

	/* If either subtree is NULL, replace node with subtree */
	if(p->left == NULL)	{
		*node = p->right;
	} else if(p->right == NULL)	{
		*node = p->left;

	/* Otherwise find the successor -- left-most of right subtree -- replace
	 * node's value with that of the successor, and remove the successor by
	 * replacing it with its possible right subtree.
	 */
	} else {
		struct btnode **n;
		n = &p->right;
		while((*n)->left)
			n = &(*n)->left;
		(*node)->data = (*n)->data;
		/* Here we want to free this one, not the actual node so we save it */
		p = *n;
		*n = (*n)->right;
	}
	free(p);

	return 0;
}
