#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 10

struct stack {
  void *data;
  size_t type_size;
  size_t count;
  size_t capacity;
};

stack *create_stack(size_t ts) {
  stack *s = malloc(sizeof(stack));
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

int stack_push(stack *s, void *i) {
  if (s == NULL) {
    return 1;
  }
  if (s->count == s->capacity) {
    size_t temp_cap = s->capacity + INITIAL_CAP;
    void *temp_block = realloc(s->data, temp_cap * s->type_size);
    if (temp_block == NULL) {
      return 1;
    }
    s->data = temp_block;
    s->capacity = temp_cap;
  }
  memcpy((char *)s->data + s->count * s->type_size, i, s->type_size);
  s->count++;
  return 0;
}

int stack_pop(stack *s, void *o) {
  if (s == NULL || s->count == 0) {
    return 1;
  }
  memcpy(o, (char *)s->data + s->type_size * (s->count - 1), s->type_size);
  s->count--;
  return 0;
}

void *stack_peek(stack *s) {
  if (s == NULL || s->count == 0) {
    return NULL;
  }
  void *i = (char *)s->data + s->type_size * (s->count - 1);
  return i;
}

int stack_clear(stack *s) {
  if (s == NULL) {
    return 1;
  }
  void *temp_block = realloc(s->data, s->type_size * INITIAL_CAP);
  if (temp_block == NULL) {
    return 1;
  }
  s->data = temp_block;
  s->count = 0;
  s->capacity = INITIAL_CAP;
  return 0;
}

size_t stack_count(stack *s) { return s->count; }

int free_stack(stack **s) {
  if (s==NULL||*s == NULL) {
    return 1;
  }
  free((*s)->data);
  free(*s);
  *s = NULL;
  return 0;
}
