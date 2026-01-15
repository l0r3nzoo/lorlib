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
  str->data[str->size] = '\0';
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
  if (self == NULL || s == NULL) {
    return 1;
  }
  size_t len = strlen(s);
  if (self->size + len + 1 > self->capacity) {
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
  if (self == NULL||s==NULL) {
    return 1;
  }
  size_t len = strlen(s);
  if (self->size + len + 1 > self->capacity) {
    size_t temp_cap = self->size + len + INITIAL_CAP;
    char *temp_data = realloc(self->data, sizeof(char) * temp_cap);
    if (temp_data == NULL) {
      return 1;
    }
    self->data = temp_data;
    self->capacity = temp_cap;
  }
  memmove(self->data + len, self->data,
          self->size + 1); // +1 for null terminator
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

  self->data[start] = '\0';
  self->size = start;
  return 0;
}

int string_replace_char(string *self, char oldchar, char newchar) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  for (size_t i = 0; i < self->size; i++) {
    if (self->data[i] == oldchar) {
      self->data[i] = newchar;
    }
  }
  return 0;
}

int string_replace_str(string *self, const char *oldstr, const char *newstr) {
  if (!self || !self->data || !oldstr || !newstr)
    return 1;

  size_t oldlen = strlen(oldstr);
  size_t newlen = strlen(newstr);
  if (oldlen == 0 || oldlen > self->size)
    return 0;

  for (size_t i = 0; i + oldlen <= self->size;) {
    if (memcmp(self->data + i, oldstr, oldlen) == 0) {

      if (newlen > oldlen) {
        size_t needed = self->size + (newlen - oldlen) + 1;
        if (needed > self->capacity) {
          size_t cap = needed + INITIAL_CAP;
          char *tmp = realloc(self->data, cap);
          if (!tmp)
            return 1;
          self->data = tmp;
          self->capacity = cap;
        }
      }

      memmove(self->data + i + newlen, self->data + i + oldlen,
              self->size - i - oldlen + 1);

      memcpy(self->data + i, newstr, newlen);
      self->size = self->size - oldlen + newlen;
      i += newlen;
    } else {
      i++;
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
  for (size_t i = 0; i < self->size; i++) {
    self->data[i] = toupper(self->data[i]);
  }
  return 0;
}

int string_tolower(string *self) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  for (size_t i = 0; i < self->size; i++) {
    self->data[i] = tolower(self->data[i]);
  }
  return 0;
}

int string_reverse(string *self) {
  if (self == NULL || self->data == NULL) {
    return 1;
  }
  if (self->size == 0) {
    return 0;
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

vector *string_split_char(string *self, char c) {
  if (self == NULL || self->data == NULL) {
    return NULL;
  }

  vector *strvector = create_vector(sizeof(string));
  size_t index = 0;

  for (size_t i = 0; i < self->size; i++) {
    if (self->data[i] == c) {
      size_t length = i - index;
      string splitstring;
      init_string(&splitstring);
      if (length > 0) {
        char *splitbuffer = malloc(length + 1);
        if (splitbuffer == NULL) {
          return NULL;
        }
        memcpy(splitbuffer, self->data + index, length);
        splitbuffer[length] = '\0';
        string_append_str(&splitstring, splitbuffer);
        free(splitbuffer);
      }
      vec_push(strvector, &splitstring);
      index = i + 1;
    }
  }

  if (index < self->size) {
    size_t length = self->size - index;
    string splitstring;
    init_string(&splitstring);
    char *splitbuffer = malloc(length + 1);
    if (splitbuffer == NULL) {
      return NULL;
    }
    memcpy(splitbuffer, self->data + index, length);
    splitbuffer[length] = '\0';
    string_append_str(&splitstring, splitbuffer);
    free(splitbuffer);
    vec_push(strvector, &splitstring);
  }

  return strvector;
}

int init_string(string *str) {
  if (str == NULL) {
    return 1;
  }
  str->data = malloc(sizeof(char) * INITIAL_CAP);
  if (str->data == NULL) {
    return 1;
  }
  str->capacity = INITIAL_CAP;
  str->size = 0;
  str->data[str->size] = '\0';
  return 0;
}

int destroy_string(string *self) {
  if (self == NULL) {
    return 1;
  }
  free(self->data);
  free(self);

  return 0;
}

void cleanup_string(string *self) {
  if (self != NULL && self->data != NULL) {
    free(self->data);
    self->data = NULL;
  }
}

void free_string_vector(vector **stringvec) {
  size_t i;
  string *item = NULL;
  size_t count = vec_count(*stringvec);
  for (i = 0; i < count; i++) {
    item = (string *)vec_at(*stringvec, i);
    cleanup_string(item);
  }
  free_vector(stringvec);
}

size_t string_length(string *self) { return self ? self->size : 0; }

int string_indexof_char(string *self, char c) {
  if (self == NULL) {
    return -1;
  }
  for (size_t i = 0; i < self->size; i++) {
    if (self->data[i] == c) {
      return i;
    }
  }
  return -1;
}

int string_lastindexof_char(string *self, char c) {
  if (!self || self->size == 0)
    return -1;

  for (size_t i = self->size; i-- > 0;) {
    if (self->data[i] == c)
      return (int)i;
  }
  return -1;
}

bool string_isempty(string *self) {
  if (self == NULL) {
    return true;
  }
  return self->size == 0 ? true : false;
}

bool string_contains_char(string *self, char c) {
  if (self == NULL) {
    return false;
  }
  for (int i = 0; i < self->size; i++) {
    if (self->data[i] == c) {
      return true;
    }
  }
  return false;
}

bool string_startswith_char(string *self, char c) {
  if (self == NULL || self->size == 0) {
    return false;
  }
  if (self->data[0] == c) {
    return true;
  }
  return false;
}

bool string_endswith_char(string *self, char c) {
  if (self == NULL || self->size == 0) {
    return false;
  }
  if (self->data[self->size - 1] == c) {
    return true;
  }
  return false;
}

string *string_join(char seperator, vector *strings) {
  string *str = create_string();
  size_t veclen = vec_count(strings);
  if (veclen == 0) {
    return str;
  }
  size_t i;
  string *item = NULL;
  for (i = 0; i < veclen; i++) {
    if (i != 0) {
      string_append_char(str, seperator);
    }
    item = (string *)vec_at(strings, i);
    string_append_str(str, string_cstr(item));
  }
  return str;
}

string *string_concat(vector *strings) {
  string *str = create_string();
  size_t veclen = vec_count(strings);
  if (veclen == 0) {
    return str;
  }
  size_t i;
  string *item = NULL;
  for (i = 0; i < veclen; i++) {
    item = (string *)vec_at(strings, i);
    string_append_str(str, string_cstr(item));
  }
  return str;
}

vector *string_split_str(string *self, const char *s) {
  if (!self || !self->data || !s)
    return NULL;

  size_t len = strlen(s);
  if (len == 0 || len > self->size)
    return NULL;

  vector *v = create_vector(sizeof(string));
  size_t start = 0;

  for (size_t i = 0; i <= self->size - len;) {
    if (memcmp(self->data + i, s, len) == 0) {
      size_t part_len = i - start;

      string part;
      init_string(&part);
      if (part_len > 0) {
        char *buf = malloc(part_len + 1);
        memcpy(buf, self->data + start, part_len);
        buf[part_len] = '\0';
        string_append_str(&part, buf);
        free(buf);
      }
      vec_push(v, &part);

      i += len;
      start = i;
    } else {
      i++;
    }
  }

  if (start < self->size) {
    size_t part_len = self->size - start;
    string part;
    init_string(&part);

    char *buf = malloc(part_len + 1);
    memcpy(buf, self->data + start, part_len);
    buf[part_len] = '\0';
    string_append_str(&part, buf);
    free(buf);

    vec_push(v, &part);
  }

  return v;
}

int string_indexof_str(string *self, const char *s) {
  if (!self || !self->data || !s)
    return -1;

  size_t len = strlen(s);
  if (len == 0 || len > self->size)
    return -1;

  for (size_t i = 0; i <= self->size - len; i++)
    if (memcmp(self->data + i, s, len) == 0)
      return (int)i;

  return -1;
}

int string_lastindexof_str(string *self, const char *s) {
  if (!self || !self->data || !s)
    return -1;

  size_t len = strlen(s);
  if (len == 0 || len > self->size)
    return -1;

  for (size_t i = self->size - len + 1; i-- > 0;)
    if (memcmp(self->data + i, s, len) == 0)
      return (int)i;

  return -1;
}

bool string_contains_str(string *self, const char *s) {
  return string_indexof_str(self, s) != -1;
}

bool string_startswith_str(string *self, const char *s) {
  if (!self || !self->data || !s)
    return false;

  size_t len = strlen(s);
  if (len == 0 || len > self->size)
    return false;

  return memcmp(self->data, s, len) == 0;
}

bool string_endswith_str(string *self, const char *s) {
  if (!self || !self->data || !s)
    return false;

  size_t len = strlen(s);
  if (len == 0 || len > self->size)
    return false;

  return memcmp(self->data + self->size - len, s, len) == 0;
}
