#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#ifndef STRING_H
#define STRING_H

typedef struct string string;
string *create_string(void); //DONE
string *string_join(char seperator, vector *strings);
string *string_concat(vector *string);



const char *string_cstr(string *self); //DONE

int clear_string(string *self); //DONE
int string_prepend_char(string *self, char c);
int string_prepend_str(string *self, const char *s);
int string_append_char(string *self, char c); //DONE
int string_append_str(string *self, const char *s); //DONE
int string_remove_range(string *self, size_t start, size_t count);
int string_remove_from(string *self, size_t start);
int string_replace_char(string *self, char c);
int string_replace_str(string *self, const char *s);
int string_trim(string *self, char c);
int string_toupper(string *self);
int string_tolower(string *self);
int string_reverse(string *self);

vector *string_split_char(string *self, char c);
vector *string_split_str(string *self, const char *s);

size_t string_length(string *self);
size_t string_indexof_char(string *self, char c);
size_t string_indexof_str(string *self, const char *s);
size_t string_lastindexof_char(string *self, char c);
size_t string_lastindexof_str(string *self, const char *s);

bool string_isempty(string *self);
bool string_contains_char(string *self, char c);
bool string_contains_str(string *self, const char *s);
bool string_startswith_char(string *self, char c);
bool string_startswith_str(string *self, const char *s);
bool string_endswith_char(string *self, char c);
bool string_endswith_str(string *self, const char *s);

int free_string(string **self); //DONE

#endif
