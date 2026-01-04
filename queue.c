#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 10

struct queue {
  void *data;
  size_t type_size;
  size_t count;
  size_t capacity;
};

queue *create_queue(size_t ts) {
  queue *s = malloc(sizeof(queue));
  if (s == NULL) {
    return NULL;
  }
  s->data = malloc(ts * INITIAL_CAP);
  if (s->data == NULL) {
    free(s);
    return NULL;
  }
  s->capacity = INITIAL_CAP;
  s->count = 0;
  s->type_size = ts;
  return s;
}

int queue_enqueue(queue *q, void *i) {
  if (q == NULL) {
    return 1;
  }
  if (q->count == q->capacity) {
    size_t temp_cap = q->capacity + INITIAL_CAP;
    void *temp_block = realloc(q->data, temp_cap * q->type_size);
    if (temp_block == NULL) {
      return 1;
    }
    q->data = temp_block;
    q->capacity = temp_cap;
  }
  memcpy((char *)q->data + q->count * q->type_size, i, q->type_size);
  q->count++;
  return 0;
}

int queue_dequeue(queue *q, void *o) {
  if (q == NULL || q->count == 0) {
    return 1;
  }
  // copy the 0th element in the queue to the out
  memcpy(o, (char *)q->data, q->type_size);
  for (int i = 1; i < q->count; i++) {
    memcpy((char *)q->data + q->type_size * (i - 1),
           (char *)q->data + q->type_size * i, q->type_size);
  }
  q->count--;
  return 0;
}

void *queue_peek(queue *q) {
  if (q == NULL || q->count == 0) {
    return NULL;
  }
  void *i = (char *)q->data + q->type_size * (q->count - 1);
  return i;
}

int queue_clear(queue *q) {
  if (q == NULL) {
    return 1;
  }
  void *temp_block = realloc(q->data, q->type_size * INITIAL_CAP);
  if (temp_block == NULL) {
    return 1;
  }
  q->data = temp_block;
  q->count = 0;
  q->capacity = INITIAL_CAP;
  return 0;
}

size_t queue_count(queue *q) { return q->count; }

int free_queue(queue **q) {
  if (q == NULL || *q == NULL) {
    return 1;
  }
  free((*q)->data);
  free(*q);
  *q = NULL;
  return 0;
}
