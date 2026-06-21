#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct Queue Queue;

Queue *queue_init(void);
void queue_free(Queue *q);

void queue_push(Queue *q, void *p);
void *queue_pop(Queue *q);
void *queue_peek(const Queue *q);
bool queue_is_empty(const Queue *q);

#endif