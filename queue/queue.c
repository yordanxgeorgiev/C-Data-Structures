#include <stdlib.h>
#include "queue.h"

#define QUEUE_DEFAULT_SIZE 100

struct queue
{
    int capacity;
    int size;
    int left;
    int right;
    void **data;
};

queue *queue_init(void)
{
    queue *q = malloc(sizeof(queue));
    q->capacity = QUEUE_DEFAULT_SIZE;
    q->size = 0;
    q->left = 0;
    q->right = 0;
    q->data = malloc(q->capacity * sizeof(void *));
    return q;
}

void queue_free(queue *q)
{
    free(q->data);
    free(q);
}

void queue_push(queue *q, void *p)
{
    if (q->size == q->capacity)
    {
        q->capacity *= 2;
        void **new_data = malloc(q->capacity * sizeof(void *));

        for (int i = 0; i < q->size; i++)
        {
            new_data[i] = q->data[(q->left + i) % q->size];
        }

        free(q->data);
        q->data = new_data;
        q->left = 0;
        q->right = q->size;
    }

    q->data[q->right] = p;
    q->right = (q->right + 1) % q->capacity;
    q->size++;
}

void *queue_pop(queue *q)
{
    if (q->size <= 0)
    {
        return NULL;
    }

    void *val = q->data[q->left];
    q->left = (q->left + 1) % q->capacity;
    q->size--;

    return val;
}

void *queue_peek(const queue *q)
{
    if (q->size <= 0)
    {
        return NULL;
    }

    return q->data[q->left];
}

bool queue_is_empty(const queue *q)
{
    return q->size <= 0;
}