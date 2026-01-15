#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#ifndef STRING_H
#define STRING_H

typedef struct string string;
string *create_string(void);                          // DONE
string *string_join(char seperator, vector *strings); // DONE
string *string_concat(vector *strings);               // DONE
int init_string(string *str);                         // DONE

const char *string_cstr(string *self); // DONE

int clear_string(string *self);                                    // DONE
int string_prepend_char(string *self, char c);                     // DONE
int string_prepend_str(string *self, const char *s);               // DONE
int string_append_char(string *self, char c);                      // DONE
int string_append_str(string *self, const char *s);                // DONE
int string_remove_range(string *self, size_t start, size_t count); // DONE
int string_remove_from(string *self, size_t start);                // DONE
int string_replace_char(string *self, char oldchar, char newchar); // DONE
int string_replace_str(string *self, const char *oldstr,
                       const char *newstr); // DONE
int string_trim(string *self, char c);      // DONE
int string_toupper(string *self);           // DONE
int string_tolower(string *self);           // DONE
int string_reverse(string *self);           // DONE

vector *string_split_char(string *self, char c);       // DONE
vector *string_split_str(string *self, const char *s); // DONE

size_t string_length(string *self);                      // DONE
int string_indexof_char(string *self, char c);           // DONE
int string_indexof_str(string *self, const char *s);     // DONE
int string_lastindexof_char(string *self, char c);       // DONE
int string_lastindexof_str(string *self, const char *s); // DONE

bool string_isempty(string *self);                       // DONE
bool string_contains_char(string *self, char c);         // DONE
bool string_contains_str(string *self, const char *s);   // DONE
bool string_startswith_char(string *self, char c);       // DONE
bool string_startswith_str(string *self, const char *s); // DONE
bool string_endswith_char(string *self, char c);         // DONE
bool string_endswith_str(string *self, const char *s);   // DONE

int free_string(string **self);              // DONE
int destroy_string(string *self);            // DONE
void free_string_vector(vector **stringvec); // DONE

#endif
