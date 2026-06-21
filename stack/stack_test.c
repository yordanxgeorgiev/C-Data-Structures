#include <stdio.h>
#include "stack.h"

int main()
{
    stack *s = stack_init();

    int a = 10, b = 20, c = 30;

    printf("Pushing values...\n");
    stack_push(s, &a);
    stack_push(s, &b);
    stack_push(s, &c);

    printf("Top element: %d\n", *(int *)stack_peek(s));

    printf("\nPopping:\n");
    while (!stack_is_empty(s))
    {
        int *val = (int *)stack_pop(s);
        printf("%d\n", *val);
    }

    printf("\nStack empty? %s\n",
           stack_is_empty(s) ? "yes" : "no");

    stack_free(s);
    return 0;
}