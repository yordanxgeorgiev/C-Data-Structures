#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

int main(void)
{
    queue *q = queue_init();

    assert(queue_is_empty(q));

    int a = 1, b = 2, c = 3, d = 4;

    queue_push(q, &a);
    queue_push(q, &b);
    queue_push(q, &c);

    assert(!queue_is_empty(q));

    int *x = queue_pop(q);
    assert(*x == 1);

    int *y = queue_peek(q);
    assert(*y == 2);

    queue_push(q, &d);

    int *z1 = queue_pop(q);
    int *z2 = queue_pop(q);
    int *z3 = queue_pop(q);

    assert(*z1 == 2);
    assert(*z2 == 3);
    assert(*z3 == 4);

    assert(queue_is_empty(q));

    for (int i = 0; i < 200; i++)
    {
        int *v = malloc(sizeof(int));
        *v = i;
        queue_push(q, v);
    }

    for (int i = 0; i < 200; i++)
    {
        int *v = queue_pop(q);
        assert(*v == i);
    }

    assert(queue_is_empty(q));

    queue_free(q);

    printf("All queue tests passed!\n");

    return 0;
}