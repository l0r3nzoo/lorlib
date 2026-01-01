#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct dictionary dictionary;
typedef struct kv_pair kv_pair;

dictionary *create_dictionary(size_t key_s, size_t value_s);
int dict_add(dictionary *dict, void *key, void *value);
bool dict_tryadd(dictionary *dict, void *key, void *value);
bool dict_tryget_value(dictionary *dict, void *key, void *out);
int dict_replace(dictionary *dict, void *key, void *value);
int dict_remove(dictionary *dict, void *key);
bool dict_contains_key(dictionary *dict, void *key);
bool dict_contains_value(dictionary *dict, void *value);
int dict_clear(dictionary *dict);
int free_dictionary(dictionary **dict);

#endif
