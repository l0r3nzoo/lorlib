#include "string.h"
#include "vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 10

struct string {
  char *data;
  size_t size;
  size_t capacity;
};

string *create_string(void) {
  string *str = malloc(sizeof(string));
  if (str == NULL) {
    return NULL;
  }
  str->data = malloc(sizeof(char) * INITIAL_CAP);
  if (str->data == NULL) {
    free(str);
    return NULL;
  }
  str->capacity = INITIAL_CAP;
  str->size = 0;
  return str;
}
int string_append_char(string *self, char c) {
  if (self == NULL) {
    return 1;
  }
  if (self->size + 1 >= self->capacity) {
    size_t temp_cap = self->capacity + INITIAL_CAP;
    char *temp_data = realloc(self->data, sizeof(char) * temp_cap);
    if (temp_data == NULL) {
      return 1;
    }
    self->data = temp_data;
    self->capacity = temp_cap;
  }
  self->data[self->size] = c;
  self->size++;
  self->data[self->size] = '\0';
  return 0;
}
int string_append_str(string *self, const char *s) {
  if (self == NULL) {
    return 1;
  }
  size_t len = strlen(s);
  if (self->size + 1 >= self->capacity) {
    size_t temp_cap = self->size + len + INITIAL_CAP;
    char *temp_data = realloc(self->data, sizeof(char) * temp_cap);
    if (temp_data == NULL) {
      return 1;
    }
    self->data = temp_data;
    self->capacity = temp_cap;
  }
  memcpy(self->data + self->size, s, len);
  self->size += len;
  self->data[self->size] = '\0';
  return 0;
}
const char *string_cstr(string *self) {
  if (self == NULL) {
    return NULL;
  }
  if (self->data == NULL) {
    return NULL;
  }
  return self->data;
}
int clear_string(string *self) {
  if (self == NULL) {
    return 1;
  }
  if (self->data == NULL) {
    return 1;
  }
  self->size = 0;
  self->data[self->size] = '\0';
  return 0;
}
int free_string(string **self) {
  if (self == NULL || *self == NULL) {
    return 1;
  }
  free((*self)->data);
  free(*self);
  *self = NULL;
  return 0;
}

int string_prepend_char(string *self, char c) {
  if (self == NULL) {
    return 1;
  }
  if (self->data == NULL) {
    return 1;
  }
  if (self->size + 1 >= self->capacity) {
    size_t temp_cap = self->capacity + INITIAL_CAP;
    char *temp_data = realloc(self->data, sizeof(char) * temp_cap);
    if (temp_data == NULL) {
      return 1;
    }
    self->data = temp_data;
    self->capacity = temp_cap;
  }
  self->size++;
  for (size_t i = 0; i < self->size; i++) {

  }
  self->data[self->size] = '\0';
  return 0;
}
