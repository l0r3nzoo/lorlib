#include "string.h"
#include <stdio.h>

int main() {
  string *string = create_string();
  string_append_str(string, "hello guys");

  const char *first = string_cstr(string);
  printf("append str '%s'\n", first);

  string_append_char(string, 'c');

  const char *second = string_cstr(string);
  printf("append char c '%s'\n", second);

  string_prepend_char(string, 'c');

  const char *third = string_cstr(string);
  printf("prepend char c '%s'\n", third);

  string_prepend_str(string, "niggers");

  const char *fourth = string_cstr(string);
  printf("prepend str '%s'\n", fourth);
  clear_string(string);
  free_string(&string);
}
