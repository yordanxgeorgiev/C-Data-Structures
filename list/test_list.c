#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void)
{
    List *l = init_list(sizeof(int));

    int values[] = {7, 2, 9, 1, 5, 3, 8, 6, 4, 0};

    // Append elements
    for (int i = 0; i < 10; i++)
    {
        list_append(l, &values[i]);
    }

    printf("Before sort:\n");
    for (int i = 0; i < l->size; i++)
    {
        int v;
        list_get(l, i, &v);
        printf("%d ", v);
    }
    printf("\n");

    // Sort
    list_sort(l, cmp_int);

    printf("After sort:\n");
    for (int i = 0; i < l->size; i++)
    {
        int v;
        list_get(l, i, &v);
        printf("%d ", v);
    }
    printf("\n");

    // Pop test after sorting
    printf("Pop after sort:\n");
    while (l->size > 0)
    {
        int v;
        list_pop(l, &v);
        printf("%d ", v);
    }
    printf("\n");

    free_list(l);
    return 0;
}