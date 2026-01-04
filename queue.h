#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>

typedef struct queue queue;

queue *create_queue(size_t ts);

int queue_enqueue(queue *s, void *i);
int queue_dequeue(queue *s, void *o);
void *queue_peek(queue *s);
int queue_clear(queue *s);
int free_queue(queue **s);
size_t queue_count(queue *s);

#endif
