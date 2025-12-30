#ifndef STACK_H
#define STACK_H
#include <stddef.h>

typedef struct stack stack;

/// Initializes stack, Index starts from 0, capacity is set internally
/// @param `ts` size of the type for the stack
/// @return pointer to the vector on SUCCESS, NULL on FAILURE
stack *create_stack(size_t ts);

/// Pushes item to the stack
/// @param `*s` pointer to the stack
/// @param `*i` pointer to the item to be pushed to stack
/// @return `0` on SUCCESS, `1` on FAILURE
int stack_push(stack *s, void *i);
int stack_pop(stack *s, void *o);
void *stack_peek(stack *s);
int stack_clear(stack *s);
int free_stack(stack **s);
size_t stack_count(stack *s);

#endif
