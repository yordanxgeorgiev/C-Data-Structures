#include <stdlib.h>
#include <string.h>
#include "list.h"

#define DEFAULT_CAPACITY 50

List *init_list(int elem_size)
{
    List *arr = malloc(sizeof(List));

    arr->size = 0;
    arr->capacity = DEFAULT_CAPACITY;
    arr->elem_size = elem_size;
    arr->data = malloc(arr->capacity * arr->elem_size);

    return arr;
}

void free_list(List *arr)
{
    free(arr->data);
    free(arr);
}

void *index_pointer(List *arr, int i)
{
    return (char *)arr->data + (i * arr->elem_size);
}

void list_get(List *arr, int i, void *out)
{
    memcpy(out, index_pointer(arr, i), arr->elem_size);
}

void list_set(List *arr, int i, void *p)
{
    memcpy(index_pointer(arr, i), p, arr->elem_size);
}

void list_append(List *arr, void *p)
{
    if (arr->size == arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * arr->elem_size);
    }

    list_set(arr, arr->size++, p);
}

void list_pop(List *arr, void *out)
{
    if (arr->size == 0)
        return;

    list_get(arr, --arr->size, out);
}

void list_sort(List *arr, int (*cmp)(const void *, const void *))
{
    qsort(arr->data, arr->size, arr->elem_size, cmp);
}