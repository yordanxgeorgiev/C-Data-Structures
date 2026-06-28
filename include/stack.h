#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

Stack *stack_init(void);
void stack_free(Stack *s);

void stack_push(Stack *s, void *p);
void *stack_pop(Stack *s);
void *stack_peek(const Stack *s);
bool stack_is_empty(const Stack *s);

#endif