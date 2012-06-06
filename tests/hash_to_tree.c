#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash.h"
#include "tree.h"


void inorder_dot(struct btnode *b)
{
	if(b == NULL)
		return;
	inorder_dot(b->left);
	inorder_dot(b->right);
	if(b->left)
		printf("\t%s -> %s\n", (char *)b->data, (char *)b->left->data);
	if(b->right)
		printf("\t%s -> %s\n", (char *)b->data, (char *)b->right->data);
}

void fill_words(hash_table *h, char *file, int n)
{
	FILE *fp = fopen(file, "r");
	char buf[1024];
	int i = 0;
	if(fp == NULL)	{
		printf("Cannot open %s\n", file);
		exit(1);
	}

	while(fgets(buf, 1024, fp) != NULL)	{
		buf[strlen(buf) - 1] = '\0';
		hash_insert(h, buf, "what");
		if(++i > n && n > 0)
			break;
	}
	fclose(fp);
}

int my_strcmp(void *a, void *b)
{
	return strcmp((char *)a, (char *)b);
}

int main(int argc, char const *argv[])
{
	hash_table *hash;
	hash_iter iter;
	binary_tree *tree;
	void *key, *val;

	hash = hash_init(NULL, 70);
	tree = init_bintree(&my_strcmp);

	//hash_set_autofree(hash);
	hash_set_autogrow(hash, 1.0, 1.92);

	fill_words(hash, "data/wordlist.txt", 400);


	hash_iter_init(hash, &iter);
	while(hash_iterate(hash, &iter, &key, &val) != 0)	{
		char *k = key;
		bintree_insert(tree, k);
	}
	puts("digraph this {");
	inorder_dot(tree->root);
	puts("}");
	destroy_bintree(tree);
	hash_destroy(hash);
	return 0;
}

