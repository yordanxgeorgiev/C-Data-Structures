#include <stdlib.h>
#include "stack.h"

#define STACK_DEFAULT_SIZE 100

struct Stack
{
    int capacity;
    int size;
    void **data;
};

Stack *stack_init(void)
{
    Stack *s = malloc(sizeof(Stack));
    s->capacity = STACK_DEFAULT_SIZE;
    s->data = malloc(s->capacity * sizeof(void *));
    s->size = 0;
    return s;
}

void stack_free(Stack *s)
{
    free(s->data);
    free(s);
}

void stack_push(Stack *s, void *p)
{
    if (s->size == s->capacity)
    {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(void *));
    }

    s->data[s->size++] = p;
}

void *stack_pop(Stack *s)
{
    if (s->size <= 0)
        return NULL;

    return s->data[--s->size];
}

void *stack_peek(const Stack *s)
{
    if (s->size <= 0)
        return NULL;

    return s->data[s->size - 1];
}

bool stack_is_empty(const Stack *s)
{
    return s->size <= 0;
}