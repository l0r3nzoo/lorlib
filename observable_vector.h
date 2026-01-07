#ifndef OBSERVABLE_VECTOR_H
#define OBSERVABLE_VECTOR_H

#include <stddef.h>

#define ITEM_ADDED 1
#define ITEM_REMOVED 2
#define VECTOR_CLEARED 3
#define VECTOR_FREED 4

typedef void(*vector_changed)(int);

typedef struct observable_vector observable_vector;

observable_vector *create_observable_vector(size_t ts);
int o_vec_push(observable_vector *v, void *i);
int o_vec_remove(observable_vector *v, void *i);
int o_vec_remove_at(observable_vector *v, size_t i);
int o_vec_clear(observable_vector *v);
size_t o_vec_index_of(observable_vector *v, void *i);
int free_observable_vector(observable_vector **v);
size_t o_vec_count(observable_vector *v);
void set_callback(vector_changed callback);

#endif
