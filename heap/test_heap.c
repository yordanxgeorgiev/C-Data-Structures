#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/* ---------- comparator (MIN HEAP) ---------- */
int int_cmp(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return ia - ib;
}

/* ---------- helper ---------- */
int *make_int(int v)
{
    int *p = malloc(sizeof(int));
    *p = v;
    return p;
}

/* ---------- test basic push/pop ordering ---------- */
void test_order()
{
    printf("Test: order\n");

    Heap *h = heap_init(int_cmp);

    int values[] = {5, 1, 9, 3, 7};

    for (int i = 0; i < 5; i++)
        heap_push(h, make_int(values[i]));

    while (!heap_is_empty(h))
    {
        int *v = heap_pop(h);
        printf("%d ", *v);
        free(v);
    }

    printf("\n(expected: 1 3 5 7 9)\n\n");
    heap_free(h);
}

/* ---------- test peek ---------- */
void test_peek()
{
    printf("Test: peek\n");

    Heap *h = heap_init(int_cmp);

    heap_push(h, make_int(10));
    heap_push(h, make_int(2));
    heap_push(h, make_int(8));

    int *p = heap_peek(h);
    printf("peek = %d (expected: 2)\n\n", *p);

    heap_free(h);
}

/* ---------- test empty ---------- */
void test_empty()
{
    printf("Test: empty\n");

    Heap *h = heap_init(int_cmp);

    printf("empty? %d (expected: 1)\n", heap_is_empty(h));

    heap_push(h, make_int(1));

    printf("empty? %d (expected: 0)\n", heap_is_empty(h));

    heap_pop(h);

    printf("empty? %d (expected: 1)\n\n", heap_is_empty(h));

    heap_free(h);
}

/* ---------- stress test ---------- */
void test_stress()
{
    printf("Test: stress\n");

    Heap *h = heap_init(int_cmp);

    for (int i = 1000; i >= 1; i--)
        heap_push(h, make_int(i));

    int prev = -1;

    while (!heap_is_empty(h))
    {
        int v = *(int *)heap_pop(h);
        if (prev != -1 && v < prev)
        {
            printf("ERROR: heap order broken\n");
            break;
        }
        prev = v;
    }

    printf("stress test done\n\n");

    heap_free(h);
}

/* ---------- main ---------- */
int main()
{
    test_order();
    test_peek();
    test_empty();
    test_stress();

    return 0;
}