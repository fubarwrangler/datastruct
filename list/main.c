#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sllist.h"

void *myupper(void *str)
{
    char *p;
    p = str;
    while(*p)
    {
        *p = toupper(*p);
        *p++;
    }
    return str;
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

void list_printer(linked_list *lst)
{
    list_node *p = lst->head;
    int ctr=0;

    while(p)
    {
        printf("%8x: (%2d) %s (%d) (next -> %x)\n", p, ctr++, (char *)p->data, p->len, p->next);
        p = p->next;
    }
}


int main(int argc, char *argv[])
{
    FILE *fp;
    char tmp[512];
    linked_list *words;
    list_node *p = NULL;
    linked_list *copy = NULL;
    char tstr[30] = {0};
    int i, n=0;

    if((fp = fopen("../tests/words.txt", "r")) == NULL)
    {
        printf("Error opening word file\n");
        return 1;
    }

    words = list_init();

    while((fgets(tmp, 512, fp)) != NULL && n++ < 40)
    {
        i = strlen(tmp);
        tmp[i - 1] = '\0';
        p = list_insert(words, p, tmp, i);
    }

    fclose(fp);
    strcpy(tstr, "lowercaseword_here");

    //list_printer(words);
    printf("List has %ld elements\n", list_size(words));
    list_printer(words);

    copy = list_copy(words);

    printf("Copy:\n");
    list_printer(copy);
    list_shuffle(copy);
    list_apply_each(words, myupper);
    printf("Old, uppered:\n");
    list_printer(words);
    printf("Copy, shuffled:\n");
    list_printer(copy);
    list_destroy(copy);

    list_delete_head(words);
    printf("Old, missing head:\n");
    list_printer(words);
    printf("Old, with another:\n");
    list_insert_after(words->head->next->next, tstr, strlen(tstr) + 1);
    list_printer(words);
    printf("Index of NET: %d\n", list_search(words, "NET", myfind));
    printf("Index of net: %d\n", list_search(words, "net", myfind));




    list_destroy(words);

    return 0;
}
