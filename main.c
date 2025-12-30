#include "stack.h"
#include "vector.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
  stack *s = create_stack(sizeof(int));
  assert(s);

  int a = 10, b = 20, out;

  assert(stack_push(s, &a) == 0);
  assert(stack_push(s, &b) == 0);
  assert(stack_count(s) == 2);

  assert(stack_pop(s, &out) == 0);
  assert(out == 20);
  assert(stack_count(s) == 1);

  int *peek = stack_peek(s);
  assert(peek && *peek == 10);

  assert(stack_pop(s, &out) == 0);
  assert(out == 10);
  assert(stack_count(s) == 0);

  assert(stack_clear(s) == 0);
  assert(stack_count(s) == 0);

  assert(free_stack(&s) == 0);
  assert(s == NULL);

  printf("All stack tests passed\n");

  vector *v = create_vector(sizeof(int));
  assert(v);

  int c = 30;

  assert(vec_push(v, &a) == 0);
  assert(vec_push(v, &b) == 0);
  assert(vec_push(v, &c) == 0);
  assert(vec_count(v) == 3);

  assert(vec_index_of(v, &a) == 0);
  assert(vec_index_of(v, &b) == 1);
  assert(vec_index_of(v, &c) == 2);

  assert(vec_remove(v, &b) == 0);
  assert(vec_count(v) == 2);
  assert(vec_index_of(v, &b) == SIZE_MAX);

  assert(vec_remove_at(v, 0) == 0);
  assert(vec_count(v) == 1);
  assert(vec_index_of(v, &a) == SIZE_MAX);

  assert(vec_clear(v) == 0);
  assert(vec_count(v) == 0);

  assert(free_vector(&v) == 0);
  assert(v == NULL);

  printf("All vector tests passed\n");
  return 0;
}
