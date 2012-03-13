#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int *mklist(int len)
{
	int i;
	int *a = malloc(len * sizeof(int));
	srand(getpid());
	for(i = 0; i < len - 2; i++)
		a[i] = 1 + (rand() % 5111);
	a[len - 1] = 0;
	return a;
}

int main(int argc, char *argv[])
{
	int a[] = {5, 31, 2, 9, 24, 12, 7, 19, 30, 35, 2, 4, 0};
	int *b, *p;
	binary_tree *bt;

	b = mklist(100);
	p = b;
	bt = init_bintree(&intcmp);

	while(*p)
		bintree_insert(bt, p++);

	puts("digraph tree2 {");
	inorder_dot(bt->root);
	puts("}\n");

	destroy_bintree(bt);

	free(b);

	return 0;

}