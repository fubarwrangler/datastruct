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

void bt_delnode(struct btnode **node)
{
	struct btnode *p, *q;

	p = *node;

	if(p->left == NULL)	{
		*node = p->right;
	} else if(p->right == NULL)	{
		*node = p->left;
	} else {
		struct btnode **tmp, **n;
		n = &p->right;
		while((*n)->left)
			n = &(*n)->left;
		(*node)->data = (*n)->data;

		/* Should only ever recurse once */
		bt_delnode(n);
		return ;
	}
	free(p);

}

int bintree_delete(struct binary_tree *bt, void *value)
{
	struct btnode **n = btn_srch(bt, value);

	if(*n == NULL)
		return 1;
	else
		bt_delnode(n);
	return 0;
}
