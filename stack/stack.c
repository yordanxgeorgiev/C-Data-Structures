#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack
{
    int capacity;
    int size;
    void **data;
};

stack *stack_init(void)
{
    stack *s = malloc(sizeof(stack));
    s->capacity = STACK_DEFAULT_SIZE;
    s->data = malloc(s->capacity * sizeof(void *));
    s->size = 0;
    return s;
}

void stack_free(stack *s)
{
    free(s->data);
    free(s);
}

void stack_push(stack *s, void *p)
{
    if (s->size == s->capacity)
    {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(void *));
    }

    s->data[s->size++] = p;
}

void *stack_pop(stack *s)
{
    if (s->size <= 0)
        return NULL;

    return s->data[--s->size];
}

void *stack_peek(stack *s)
{
    if (s->size <= 0)
        return NULL;

    return s->data[s->size - 1];
}

int stack_is_empty(stack *s)
{
    return s->size <= 0;
}