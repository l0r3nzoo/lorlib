#include <stdlib.h>
static inline void secure_zero(void *p, size_t n) {
  volatile unsigned char *vp = (volatile unsigned char *)p;
  while (n--)
    *vp++ = 0;
}
#define USING(type, var, count)                                                \
  for (type *var = malloc(sizeof(type) * (count)), *_once = (type *)1; _once;  \
       _once = NULL, secure_zero(var, sizeof(type) * (count)), free(var))
