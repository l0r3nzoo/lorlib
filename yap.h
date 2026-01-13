#ifndef YAP_H
#define YAP_H

#include <stdio.h>

#ifdef IS_COLOR
void yap_base(int fg, int bg, const char *tag, const char *msg) {
  printf("\033[%d;%dm%s - %s\033[0m\n", fg, bg, tag, msg);
}
#else

void yap_base(const char *tag, const char *msg) {
  printf("%s - %s\n", tag, msg);
}
#endif

// information
static inline void yap_info(const char *msg) {
#ifdef IS_COLOR
  yap_base(37, 40, "INFO", msg);
#else
  yap_base("INFO", msg);
#endif
}
// warning
static inline void yap_warn(const char *msg) {
#ifdef IS_COLOR
  yap_base(33, 40, "WARN", msg);
#else
  yap_base("WARN", msg);
#endif
}
// fatal
static inline void yap_fat(const char *msg) {
#ifdef IS_COLOR
  yap_base(91, 40, "FATAL", msg);
#else
  yap_base("FATAL", msg);
#endif
}
// critical
static inline void yap_clit(const char *msg) {
#ifdef IS_COLOR
  yap_base(31, 40, "CRITICAL", msg);
#else
  yap_base("CRITICAL", msg);
#endif
}

// success
static inline void yap_suck(const char *msg) {
#ifdef IS_COLOR
  yap_base(32, 40, "SUCCESS", msg);
#else
  yap_base("SUCCESS", msg);
#endif
}

#endif
