#include <stdio.h>
#include <stdlib.h>

#include "tree.h"


int intcmp(void *a, void *b)	{
	return *(int *)a - *(int *)b;
}

void inorder(struct btnode *b)
{
	if(b == NULL)
		return;
	inorder(b->left);
	printf("Node at %p: %d (left -> %p, right -> %p)\n",
		   b, *(int *)(b->data), b->left, b->right);
	inorder(b->right);
}

void postorder(struct btnode *b)
{
	if(b == NULL)
		return;
	postorder(b->left);
	postorder(b->right);
	printf("Node at %p: %d (left -> %p, right -> %p)\n",
		   b, *(int *)(b->data), b->left, b->right);
}

void preorder(struct btnode *b)
{
	if(b == NULL)
		return;
	printf("Node at %p: %d (left -> %p, right -> %p)\n",
		   b, *(int *)(b->data), b->left, b->right);
	preorder(b->left);
	preorder(b->right);
}

void inorder_dot(struct btnode *b)
{
	if(b == NULL)
		return;
	inorder_dot(b->left);
	inorder_dot(b->right);
	if(b->left)
		printf("\t%d -> %d\n", *(int *)b->data, *(int *)b->left->data);
	if(b->right)
		printf("\t%d -> %d\n", *(int *)b->data, *(int *)b->right->data);
}

int main(int argc, char *argv[])
{
	int a[] = {5, 31, 2, 9, 24, 12, 7, 19, 30, 35, 2, 4, 0};
	int *p = a;
	struct binary_tree *bt;

	bt = init_bintree(&intcmp);

	while(*p)
		bintree_insert(bt, p++);

/*	puts("digraph tree {");
	inorder_dot(bt->root);
	puts("}\n");
*/

	//bintree_delete(bt, a);
	//bintree_delete(bt, a + 1);
	bintree_delete(bt, a + 3);

	puts("digraph tree2 {");
	inorder_dot(bt->root);
	puts("}\n");


	destroy_bintree(bt);

	return 0;

}