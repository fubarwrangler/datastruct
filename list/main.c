#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sllist.h"

void *myupper(void *str)
{
    char *p;
    p = str;
    while(*p++)
        *p = toupper(*p);
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
        printf("%8x: (%2d) %18s (next -> %8x)\n", p, ctr++, (char *)p->data, p->next);
        p = p->next;
    }
}


int main(int argc, char *argv[])
{
    FILE *fp;
    char *tmp;
    linked_list *words;
    list_node *p = NULL;
    int n = 0, i;

    if((fp = fopen("../tests/wordlist.txt", "r")) == NULL)
    {
        printf("Error opening word file\n");
        return 1;
    }

    if((tmp = malloc(512)) == NULL)
    {
        printf("No memory");
        return 1;
    }
    words = list_init();

    while((fgets(tmp, 512, fp)) != NULL && n++ < 20000)
        p = list_insert(words, p, tmp, strlen(tmp) - 1);

    free(tmp);
    fclose(fp);


    //list_printer(words);
    printf("List has %ld elements\n", list_size(words));


    //list_swap_next(words->head->next->next->next->next->next->next->next->next->next,
    //               words->head->next->next->next->next->next->next->next->next->next);
    //for(i=0; i< 2000; i++)
        //list_shuffle(words);
    //list_swap_head(words, words->head);
    //list_swap_next(words->head, words->head->next);
    printf("DONE: \n");
    list_printer(words);

    //printf("Enter word to search: ");
    //scanf("%s", &item);
    //printf("Index of \"%s\": %d", item, list_search(words, item, myfind));


    list_destroy(words);

    return 0;
}