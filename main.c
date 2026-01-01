#include "dictionary.h"
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

  dictionary *dict = create_dictionary(sizeof(int), sizeof(int));
  assert(dict);

  int key1 = 1, key2 = 2, key3 = 3;
  int val1 = 10, val2 = 20, val3 = 30;
  int outdict;
  assert(dict_add(dict, &key1, &val1) == 0);
  assert(dict_add(dict, &key2, &val2) == 0);
  assert(dict_contains_key(dict, &key1) == true);
  assert(dict_contains_key(dict, &key2) == true);
  assert(dict_contains_key(dict, &key3) == false);

  assert(dict_tryadd(dict, &key3, &val3) == true);
  assert(dict_tryadd(dict, &key1, &val1) == true);

  assert(dict_tryget_value(dict, &key1, &outdict) == true);
  assert(outdict == val1);
  assert(dict_tryget_value(dict, &key3, &outdict) == true);
  assert(outdict == val3);
  int fake_key = 100;
  assert(dict_tryget_value(dict, &fake_key, &outdict) == false);

  int new_val = 99;
  assert(dict_replace(dict, &key2, &new_val) == 0);
  assert(dict_tryget_value(dict, &key2, &outdict) == true);
  assert(outdict == new_val);
  assert(dict_replace(dict, &fake_key, &new_val) == 1);

  assert(dict_contains_value(dict, &new_val) == true);
  assert(dict_contains_value(dict, &val1) == true);
  int missing_val = 123;
  assert(dict_contains_value(dict, &missing_val) == false);

  assert(dict_remove(dict, &key1) == 0);
  assert(dict_contains_key(dict, &key1) == false);
  assert(dict_tryget_value(dict, &key1, &outdict) == false);
  assert(dict_remove(dict, &fake_key) == 1);

  assert(dict_clear(dict) == 0);
  assert(dict_contains_key(dict, &key2) == false);
  assert(dict_contains_key(dict, &key3) == false);

  assert(free_dictionary(&dict) == 0);
  assert(dict == NULL);

  printf("All dictionary tests passed\n");
  return 0;
}
