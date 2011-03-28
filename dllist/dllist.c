#include <stdio.h>
#include <stdlib.h>



dllist *dllist_init(void)
{
    dllist *list;

    list = malloc(sizeof(dllist));

    if(list != NULL)
        list->head = NULL;

    return list;
}


void dllist_destroy(dllist *list);
{
    dlnode *p, *q;
    if (list != NULL)
        p = list->head;
        while(p)
        {
            q = p->next;
            free(p->data);
            free(p);
            p = q;
        }
}
