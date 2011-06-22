#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dllist.h"

void myupper(void *str)
{
    char *p;
    p = str;
    do
        *p = toupper(*p);
    while(*p++);
}

void *myprinter(void *str)
{
    printf("%s\n", (char *)str);
    return str;
}

int myfind(void *data, void *str)
{
    if(strcmp((char *)data, (char *)str) == 0)
        return 1;
    else
        return 0;
}

void list_printer(dllist *lst)
{
    dlnode *p = lst->head;
    int ctr=0;

    printf("List: head->%p, tail->%p\n", lst->head, lst->tail);
    while(p)
    {
        printf("%p: (%2d) %s (%ld) (prev -> %p) (next -> %p)\n",
               p, ctr++, (char *)p->data, p->len, p->prev, p->next);
        p = p->next;
    }
}


int main(int argc, char *argv[])
{
    FILE *fp;
    char tmp[512];
    dllist *words;
//    dlnode *p = NULL;
    int i, n=0;

    if((fp = fopen("tests/data/words.txt", "r")) == NULL)
    {
        printf("Error opening word file\n");
        return 1;
    }

    words = dllist_init();

    //dllist_append(words, "What", 5);
    while((fgets(tmp, 512, fp)) != NULL && n++ < 20)
    {
        i = strlen(tmp);
        tmp[i - 1] = '\0';
        dllist_insert(words, tmp, i);
    }

    fclose(fp);

    printf("List has %ld elements\n", dllist_size(words));
    list_printer(words);

    dllist_swap(words, DL_INDEX(words, 0), DL_INDEX(words, 6));

    printf("\nAfter swap & delete:\n");
    dllist_delete(words, words->tail->prev);
    dllist_apply_each(words, &myupper);
    list_printer(words);


    dllist_destroy(words);

    return 0;
}

