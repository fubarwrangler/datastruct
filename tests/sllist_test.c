#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sllist.h"

void *myupper(void *str)
{
    char *p;
    p = str;
    do
        *p = toupper(*p);
    while(*p++);
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
        printf("%p: (%2d) %s (%ld) (next -> %p)\n", p, ctr++, (char *)p->data, p->len, p->next);
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

    if((fp = fopen("tests/data/words.txt", "r")) == NULL)
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
    //list_destroy(copy);

    list_delete_head(words);
    printf("Old, missing head:\n");
    list_printer(words);
    printf("Old, with another:\n");
    list_insert_after(words->head->next->next, tstr, strlen(tstr) + 1);
    list_printer(words);
    p = list_create_node("Manually_insert\0", 15, 1);
    list_insert_node(words, p);
    printf("Index of NET: %d\n", list_search(words, "NET", myfind));
    printf("Index of net: %d\n", list_search(words, "net", myfind));

    list_join(words, copy);
    printf("After splice: \n");
    list_printer(words);

    printf("12th node here: %s\n", (char *)list_get_index(words, 12)->data);
    p = list_pop_next(list_get_index(words, 11));
    printf("Data from pop'd node: %s\n", p->data);
    list_destroy_node(p);
    list_printer(words);


    free(copy);
    list_destroy(words);

    return 0;
}
