#include "arena.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct arena {
  size_t size;
  char *data;
  size_t offset;
} arena;

arena *arena_create(size_t size) {
  // allocate memory to arena struct
  arena *a = malloc(sizeof(arena));
  if (a == NULL) {
    return NULL;
  }
  // allocate memory to arena->data based on the user passed size (bytes)
  a->data = malloc(size);
  if (a->data == NULL) {
    free(a);
    return NULL;
  }
  a->size = size;
  a->offset = 0;
  return a;
}

int arena_free(arena *a) {
  // return 1 (error) if arena or arena->data is not pointing to anything
  if (a == NULL || a->data == NULL) {
    return 1;
  }
  // set the memory of the arena->data to 0
  memset(a->data, 0, a->size);
  a->offset = 0;
  return 0;
}

int arena_destroy(arena **a) {
  // if a doesnt point to anything or if *a is not pointing to anything return 1
  if (a == NULL || *a == NULL) {
    return 1;
  }

  free((*a)->data);
  free(*a);
  // set *a to NULL so user cannot access the freed block
  *a = NULL;

  return 0;
}

void *arena_alloc(arena *a, size_t bytes) {
  if (a == NULL || a->data == NULL || bytes == 0) {
    return NULL;
  }
  if (a->offset + bytes > a->size) {
    return NULL;
  }
  void *data = a->data + a->offset;
  a->offset += bytes;
  return data;
}


static inline void memzero(void *p, size_t n) {
  volatile unsigned char *vp = (volatile unsigned char *)p;
  while (n--)
    *vp++ = 0;
}

void *arena_alloc_zero(arena *a, size_t bytes) {
  void *data = arena_alloc(a, bytes);
  if (data == NULL) {
    return NULL;
  }
  memzero(data, bytes);
  return data;
}

size_t arena_used(arena *a) {
  if (a == NULL) {
    return 0;
  }
  return a->offset;
}

size_t arena_remaining(arena *a) {
  if (a == NULL) {
    return 0;
  }
  return (a->size - a->offset);
}
