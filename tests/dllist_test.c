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

void mydup(void **p)
{
    char *str = (char *)*p;
    char *tmp = strdup(str);
    *p = tmp;
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

int mycmp(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

void list_printer(dllist *lst)
{
    dlnode *p = lst->head;
    int ctr=0;

    printf("List: head->%p, tail->%p\n", lst->head, lst->tail);
    while(p)
    {
        printf("%p: (%2d) %s (prev -> %p) (next -> %p)\n",
               p, ctr++, (char *)p->data, p->prev, p->next);
        p = p->next;
    }
}


int main(int argc, char *argv[])
{
    FILE *fp;
    char tmp[512];
    dllist *words, *copy;
//    dlnode *p = NULL;
    dlnode *m, *n;
    int i, j=0;

    if((fp = fopen("data/words.txt", "r")) == NULL)
    {
        printf("Error opening word file\n");
        return 1;
    }

    setbuf(stdout, NULL);

    words = dllist_init();

    //dllist_append(words, "What", 5);
    while((fgets(tmp, 512, fp)) != NULL && j++ < 9)
    {
        tmp[strlen(tmp) - 1] = NULL;
        dllist_append(words, strdup(tmp));
    }

    fclose(fp);

    m = dllist_get_index(words, 2);
    n = dllist_get_index(words, 7);
    printf("List has %ld elements\n", dllist_size(words));
    //list_printer(words);
    list_printer(words);

    copy = dllist_copy(words);

    dllist_apply_each(copy, mydup);
    //(words, DL_INDEX(words, 0), DL_INDEX(words, 6));

    printf("\nAfter swap & delete:\n");
    dllist_delete(words, words->tail->prev);
    list_printer(words);


    dllist_apply_each(copy, myupper);
    printf("Copy made uppercase: \n");
    //words = dllist_join(copy, words);
    list_printer(copy);
    printf("Orig reversed:\n");

    dllist_reverse(words);
    list_printer(words);

    printf("Address of 'net': %p\n", dllist_search(words, "net", myfind));
    printf("Index of 'LOOK': %ld\n", dllist_find_index(words, "LOOK", myfind));
    dllist_destroy(words);
    dllist_destroy(copy);

    return 0;
}

