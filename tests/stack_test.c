#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int main(int argc, char *argv[])
{
    char *values[] = {"Wisconsin", "Ohio", "Minnesota", "Kentucky"};
    stack *stk;
    stack_item *p;

    stk = stack_init();

    for(int i = 0; i < 4; i++)
        stack_push(stk, values[i], strlen(values[i]));

    printf("Peek: %s\n", stack_peek(stk));
    p = stack_pop(stk);
    printf("Popped: %s\n", p->data);
    printf("Peek: %s\n", stack_peek(stk));
    stack_destroy_item(p);
    while(stack_size(stk) > 1)
    {
        p = stack_pop(stk);
        printf("Popped: %s\n", p->data);
        stack_destroy_item(p);
    }
    printf("Pushed: Whatever\n");
    stack_push(stk, "Whatever", 9);
    p = stack_pop(stk);
    printf("Popped: %s\n", p->data);
    stack_destroy_item(p);
    p = stack_pop(stk);
    printf("Popped: %s\n", p->data);
    stack_destroy_item(p);

    stack_destroy(stk);

    return 0;
}
