#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 10

struct vector {
  void *data;
  size_t type_size;
  size_t count;
  size_t capacity;
};

vector *create_vector(size_t ts) {
  vector *v = malloc(sizeof(vector));
  if (v == NULL) {
    return NULL;
  }
  v->data = malloc(ts * INITIAL_CAP);
  if (v->data == NULL) {
    free(v);
    return NULL;
  }
  v->capacity = INITIAL_CAP;
  v->count = 0;
  v->type_size = ts;
  return v;
}

int vec_push(vector *v, void *i) {
  if (v == NULL || i == NULL) {
    return 1;
  }
  if (v->count == v->capacity) {
    size_t temp_cap = v->capacity + INITIAL_CAP;
    void *temp_block = realloc(v->data, temp_cap * v->type_size);
    if (temp_block == NULL) {
      return 1;
    }
    v->capacity = temp_cap;
    v->data = temp_block;
  }
  memcpy((char *)v->data + v->type_size * v->count, i, v->type_size);
  v->count++;
  return 0;
}

int vec_remove(vector *v, void *i) {
  if (v == NULL || v->count == 0 || i == NULL) {
    return 1;
  }
  for (size_t j = 0; j < v->count; j++) {
    void *elem = (char *)v->data + j * v->type_size;

    if (memcmp(elem, i, v->type_size) == 0) {
      if (j + 1 < v->count) {
        memmove((char *)v->data + j * v->type_size,
                (char *)v->data + (j + 1) * v->type_size,
                (v->count - j - 1) * v->type_size);
      }
      v->count--;
      return 0;
    }
  }
  return 1;
}

int vec_remove_at(vector *v, size_t i) {
  if (i >= v->count) {
    return 1;
  }
  if (i + 1 < v->count) {
    memmove((char *)v->data + i * v->type_size,
            (char *)v->data + (i + 1) * v->type_size,
            (v->count - i - 1) * v->type_size);
  }
  v->count--;
  return 0;
}

int vec_clear(vector *v) {
  if (v == NULL) {
    return 1;
  }
  void *temp_block = realloc(v->data, v->type_size * INITIAL_CAP);
  if (temp_block == NULL) {
    return 1;
  }
  v->data = temp_block;
  v->capacity = INITIAL_CAP;
  v->count = 0;
  return 0;
}

size_t vec_index_of(vector *v, void *i) {
  if (v == NULL || v->count == 0 || i == NULL) {
    return SIZE_MAX;
  }
  for (int j = 0; j < v->count; j++) {
    void *elem = (char *)v->data + j * v->type_size;
    if (memcmp(elem, i, v->type_size) == 0) {
      return j;
    }
  }
  return SIZE_MAX;
}

size_t vec_count(vector *v) { return v->count; }

int free_vector(vector **v) {
  if (v == NULL || *v == NULL) {
    return 1;
  }
  free((*v)->data);
  free(*v);
  *v = NULL;
  return 0;
}

void* vec_at(vector* v,size_t i){
    if(v==NULL || v->data==NULL){
        return NULL;
    }
    return (char*)v->data+v->type_size*i;
}
