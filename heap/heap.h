#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

typedef struct Heap Heap;
typedef int (*heap_cmp_fn)(const void *a, const void *b);

Heap *heap_init(heap_cmp_fn cmp);
void heap_free(Heap *h);

void heap_push(Heap *heap, void *p);
void *heap_pop(Heap *heap);
void *heap_peek(const Heap *heap);
bool heap_is_empty(const Heap *h);

#endif