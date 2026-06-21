#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue queue;

queue *queue_init(void);
void queue_free(queue *q);

void queue_push(queue *q, void *p);
void *queue_pop(queue *q);
void *queue_peek(const queue *q);
bool queue_is_empty(const queue *q);

#endif