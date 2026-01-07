#include "observable_vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 10

struct observable_vector {
  void *data;
  size_t type_size;
  size_t count;
  size_t capacity;
};
vector_changed on_changed_callback = NULL;
void set_callback(vector_changed callback) { on_changed_callback = callback; }

observable_vector *create_observable_vector(size_t ts) {
  observable_vector *v = malloc(sizeof(observable_vector));
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

int o_vec_push(observable_vector *v, void *i) {
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
  if (on_changed_callback) {
      on_changed_callback(ITEM_ADDED);
  }
  return 0;
}

int o_vec_remove(observable_vector *v, void *i) {
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
      if (on_changed_callback) {
          on_changed_callback(ITEM_REMOVED);
      }
      return 0;
    }
  }
  return 1;
}

int o_vec_remove_at(observable_vector *v, size_t i) {
  if (i >= v->count) {
    return 1;
  }
  if (i + 1 < v->count) {
    memmove((char *)v->data + i * v->type_size,
            (char *)v->data + (i + 1) * v->type_size,
            (v->count - i - 1) * v->type_size);
  }
  v->count--;
  if (on_changed_callback) {
      on_changed_callback(ITEM_REMOVED);
  }
  return 0;
}

int o_vec_clear(observable_vector *v) {
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
  if (on_changed_callback) {
      on_changed_callback(VECTOR_CLEARED);
  }
  return 0;
}

size_t o_vec_index_of(observable_vector *v, void *i) {
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

size_t o_vec_count(observable_vector *v) { return v->count; }

int free_observable_vector(observable_vector **v) {
  if (v == NULL || *v == NULL) {
    return 1;
  }
  free((*v)->data);
  free(*v);
  *v = NULL;
  if (on_changed_callback) {
      on_changed_callback(VECTOR_FREED);
  }
  return 0;
}
