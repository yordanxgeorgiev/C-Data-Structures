#include <stdlib.h>
#include "heap.h"

#define HEAP_DEFAULT_SIZE 100

typedef struct Heap
{
    int capacity;
    int size;
    heap_cmp_fn cmp;
    void **data;
} Heap;

Heap *heap_init(heap_cmp_fn cmp)
{
    Heap *h = malloc(sizeof(Heap));
    h->capacity = HEAP_DEFAULT_SIZE;
    h->size = 0;
    h->cmp = cmp;
    h->data = malloc(h->capacity * sizeof(void *));
    return h;
}

void heap_free(Heap *h)
{
    free(h->data);
    free(h);
}

void heap_push(Heap *h, void *p)
{
    if (h->size == h->capacity)
    {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(void *));
    }

    h->data[h->size] = p;

    int i = h->size;
    void *tmp;

    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (h->cmp(h->data[parent], h->data[i]) > 0)
        {
            tmp = h->data[parent];
            h->data[parent] = h->data[i];
            h->data[i] = tmp;
            i = parent;
        }
        else
        {
            break;
        }
    }

    h->size++;
}

void heapify_down(Heap *h, int i)
{
    while (1)
    {
        int left_i = 2 * i + 1;
        int right_i = 2 * i + 2;

        int min = i;
        if (left_i < h->size && h->cmp(h->data[left_i], h->data[min]) < 0)
        {
            min = left_i;
        }
        if (right_i < h->size && h->cmp(h->data[right_i], h->data[min]) < 0)
        {
            min = right_i;
        }

        if (min == i)
        {
            return;
        }

        void *tmp = h->data[i];
        h->data[i] = h->data[min];
        h->data[min] = tmp;

        i = min;
    }
}

void *heap_pop(Heap *h)
{
    if (h->size == 0)
        return NULL;

    void *item = h->data[0];

    h->data[0] = h->data[h->size - 1];
    h->size--;

    if (h->size > 0)
    {
        heapify_down(h, 0);
    }

    return item;
}

void *heap_peek(const Heap *h)
{
    if (h->size == 0)
        return NULL;
    return h->data[0];
}

bool heap_is_empty(const Heap *h)
{
    return h->size == 0;
}