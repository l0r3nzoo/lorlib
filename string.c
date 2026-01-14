#include "string.h"
#include "vector.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
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
  for (size_t i = self->size; i > 0; i--) {
    self->data[i] = self->data[i - 1];
  }
  self->data[0] = c;
  self->size++;
  self->data[self->size] = '\0';
  return 0;
}

int string_prepend_str(string *self, const char *s) {
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
  for (size_t i = self->size; i > 0; i--) {
    self->data[i + len - 1] = self->data[i - 1];
  }
  memcpy(self->data, s, len);
  self->size += len;
  self->data[self->size] = '\0';
  return 0;
}

int string_remove_range(string *self, size_t start, size_t count) {
  if (!self || !self->data)
    return 1;
  if (start > self->size)
    return 1;
  if (start + count > self->size)
    return 1;

  memmove(self->data + start, self->data + start + count,
          self->size - (start + count) + 1);

  self->size -= count;
  return 0;
}

int string_remove_from(string *self, size_t start) {

  if (!self || !self->data)
    return 1;
  if (start > self->size)
    return 1;

  if (start <= self->size) {
    memmove(self->data + start, self->data + self->size, 1);
    self->size = start;
    return 0;
  }
  return 1;
}

int string_replace_char(string *self, char oldchar, char newchar) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  for (int i = 0; i < self->size; i++) {
    if (self->data[i] == oldchar) {
      self->data[i] = newchar;
    }
  }
  return 0;
}

int string_replace_str(string *self, const char *oldstr, const char *newstr) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  size_t oldstrlen = strlen(oldstr);
  size_t newstrlen = strlen(newstr);
  for (int i = 0; i <= self->size - oldstrlen; i++) {
    if (strncmp(self->data + i, oldstr, oldstrlen) == 0) {
      memmove(self->data + i + newstrlen, self->data + i + oldstrlen,
              self->size - i - oldstrlen + 1);
      memcpy(self->data + i, newstr, newstrlen);
      i += newstrlen - 1;
      self->size += newstrlen - oldstrlen;
    }
  }
  return 0;
}

int string_trim(string *self, char c) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  for (size_t i = 0; i < self->size; i++) {
    if (self->data[i] == c) {
      memmove(self->data + i, self->data + i + 1, self->size - i);
      self->size--;
      i--;
    }
  }
  return 0;
}

int string_toupper(string *self) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  for (int i = 0; i < self->size; i++) {
    self->data[i] = toupper(self->data[i]);
  }
  return 0;
}

int string_tolower(string *self) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  for (int i = 0; i < self->size; i++) {
    self->data[i] = tolower(self->data[i]);
  }
  return 0;
}

int string_reverse(string *self) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  size_t j = self->size - 1;
  size_t i = 0;
  while (i < j) {
    char tmp = self->data[i];
    self->data[i] = self->data[j];
    self->data[j] = tmp;
    i++;
    j--;
  }
  return 0;
}

vector *string_split_char(string *self, char c){
    vector* strvector=create_vector(sizeof(string));
    return strvector;
}
