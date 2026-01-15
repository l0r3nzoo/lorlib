#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector vector;

/// Initializes vector, Index starts from 0, capacity is set internally
/// @param ts Size of the type for the vector such as int float char
/// @return pointer to vector on SUCCESS, NULL on FAILURE
vector *create_vector(size_t ts);

/// Pushes new item to the vector
/// @param v Pointer to the vector
/// @param i Pointer to the item to be pushed to vector
/// @return 0 on SUCCESS, 1 on FAILURE
int vec_push(vector *v, void *i);

/// remove item from the vector
/// @param v Pointer to the vector
/// @param i Pointer to the item to be removed from the vector
/// @return 0 on SUCCESS, 1 on FAILURE
int vec_remove(vector *v, void *i);

/// remove item at specific index
/// @param v Pointer to the vector
/// @param i index of the item to be removed from the vector
/// @return 0 on SUCCESS, 1 on FAILURE
int vec_remove_at(vector *v, size_t i);

/// Clear the items that the vector holding and reset the count to 0
/// @param v Pointer to the vector
/// @return 0 on SUCCESS, 1 on FAILURE
int vec_clear(vector *v);

void* vec_at(vector* v,size_t i);

/// Index of the item
/// @param v Pointer to the vector
/// @param i Pointer to the item
/// If the item is found, returns its index (0-based)
/// If the item is not found, returns `SIZE_MAX`
size_t vec_index_of(vector *v, void *i);

/// free the vector memory
/// @param v Pointer to the Pointer to the vector
///
/// This function frees the memory allocated for the vector itself
/// and also frees the memory pointed to by the vector's data field.
/// After calling this, the vector pointer is set to NULL.
/// @return 0 on SUCCESS, 1 on FAILURE
int free_vector(vector **v);
size_t vec_count(vector *v);

#endif
