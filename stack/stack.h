#ifndef STACK_H
#define STACK_H

#define STACK_DEFAULT_SIZE 100

typedef struct stack stack;

stack *stack_init(void);
void stack_free(stack *s);

void stack_push(stack *s, void *p);
void *stack_pop(stack *s);
void *stack_peek(stack *s);
int stack_is_empty(stack *s);

#endif