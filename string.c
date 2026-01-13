#include "string.h"
#include <stddef.h>
#include <stdlib.h>

#define INITIAL_CAP 10

struct string {
  char *data;
  size_t size;
  size_t capacity;
};
