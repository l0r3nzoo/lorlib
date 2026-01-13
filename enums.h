// Rust style enums for handling Optional returns and Result types
#define DEFINE_OPTION(T)                                                       \
  typedef struct {                                                             \
    int Some;                                                                  \
    T Value;                                                                   \
  } Option_##T;

#define DEFINE_RESULT(T, E)                                                    \
  typedef struct {                                                             \
    int IsOk;                                                                  \
    union {                                                                    \
      T Ok;                                                                    \
      E Err;                                                                   \
    };                                                                         \
  } Result_##T##_##E;
