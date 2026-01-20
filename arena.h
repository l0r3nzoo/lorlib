#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct arena arena;

#define MB(S) ((unsigned long)(S) * (1024UL * 1024UL))
#define KB(S) ((unsigned long)(S) * (1024UL))
#define GB(S) ((unsigned long)(S) * (1024UL * 1024UL * 1024UL))

arena *arena_create(size_t size);
void *arena_alloc(arena *a, size_t bytes);
void *arena_alloc_zero(arena *a, size_t bytes);
size_t arena_used(arena *a);
size_t arena_remaining(arena *a);
int arena_free(arena *a);
int arena_destroy(arena **a);

#endif
