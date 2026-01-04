#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 10

struct dictionary {
  size_t key_s;
  size_t value_s;
  kv_pair *pairs;
  size_t count;
  size_t capacity;
};
struct kv_pair {
  size_t key_hash;
  size_t value_hash;
  void *key;
  void *value;
};

size_t get_hash(void *data, size_t size) {
  unsigned char *bytes = (unsigned char *)data;
  size_t hash = 5381;
  for (size_t i = 0; i < size; i++) {
    hash = ((hash << 5) + hash) + bytes[i];
  }
  return hash;
}
dictionary *create_dictionary(size_t key_s, size_t value_s) {
  dictionary *dict = malloc(sizeof(dictionary));
  if (dict == NULL) {
    return NULL;
  }
  dict->pairs = malloc(sizeof(kv_pair) * INITIAL_CAP);
  if (dict->pairs == NULL) {
    return NULL;
  }
  dict->capacity = INITIAL_CAP;
  dict->count = 0;
  dict->key_s = key_s;
  dict->value_s = value_s;
  return dict;
}

bool dict_tryadd(dictionary *dict, void *key, void *value) {
  if (dict == NULL || key == NULL || value == NULL) {
    return false;
  }
  size_t key_hash = get_hash(key, dict->key_s);
  for (int i = 0; i < dict->count; i++) {

    if (dict->pairs[i].key_hash == key_hash &&
        memcmp(dict->pairs[i].key, key, dict->key_s) == 0) {
      return 1;
    }
  }
  if (dict->count == dict->capacity) {
    size_t temp_cap = dict->capacity + INITIAL_CAP;
    kv_pair *temp_pair = realloc(dict->pairs, sizeof(kv_pair) * temp_cap);
    if (temp_pair == NULL) {
      return false;
    }
    dict->capacity = temp_cap;
    dict->pairs = temp_pair;
  }
  kv_pair pair;
  pair.key = malloc(dict->key_s);
  if (pair.key == NULL) {
    return false;
  }
  pair.value = malloc(dict->value_s);
  if (pair.value == NULL) {
    free(pair.key);
    return false;
  }
  memcpy(pair.key, key, dict->key_s);
  pair.key_hash = get_hash(pair.key, dict->key_s);
  memcpy(pair.value, value, dict->value_s);
  pair.value_hash = get_hash(pair.value, dict->value_s);
  dict->pairs[dict->count] = pair;
  dict->count++;
  return true;
}
int dict_add(dictionary *dict, void *key, void *value) {
  if (dict == NULL || key == NULL || value == NULL) {
    return 1;
  }
  size_t key_hash = get_hash(key, dict->key_s);
  for (int i = 0; i < dict->count; i++) {

    if (dict->pairs[i].key_hash == key_hash &&
        memcmp(dict->pairs[i].key, key, dict->key_s) == 0) {
      return 1;
    }
  }
  if (dict->count == dict->capacity) {
    size_t temp_cap = dict->capacity + INITIAL_CAP;
    kv_pair *temp_pair = realloc(dict->pairs, sizeof(kv_pair) * temp_cap);
    if (temp_pair == NULL) {
      return 1;
    }
    dict->capacity = temp_cap;
    dict->pairs = temp_pair;
  }
  kv_pair pair;
  pair.key = malloc(dict->key_s);
  if (pair.key == NULL) {
    return 1;
  }
  pair.value = malloc(dict->value_s);
  if (pair.value == NULL) {
    free(pair.key);
    return 1;
  }
  memcpy(pair.key, key, dict->key_s);
  pair.key_hash = get_hash(pair.key, dict->key_s);
  memcpy(pair.value, value, dict->value_s);
  pair.value_hash = get_hash(pair.value, dict->value_s);
  dict->pairs[dict->count] = pair;
  dict->count++;
  return 0;
}

int dict_replace(dictionary *dict, void *key, void *value) {
  if (dict == NULL || key == NULL || value == NULL) {
    return 1;
  }
  size_t key_hash = get_hash(key, dict->key_s);
  for (int i = 0; i < dict->count; i++) {
    if (dict->pairs[i].key_hash == key_hash &&
        memcmp(dict->pairs[i].key, key, dict->key_s) == 0) {
      memcpy(dict->pairs[i].value, value, dict->value_s);
      dict->pairs[i].value_hash = get_hash(value, dict->value_s);
      return 0;
    }
  }
  return 1;
}

int dict_remove(dictionary *dict, void *key) {
  if (dict == NULL || key == NULL) {
    return 1;
  }
  size_t key_hash = get_hash(key, dict->key_s);
  for (int i = 0; i < dict->count; i++) {
    if (dict->pairs[i].key_hash == key_hash &&
        memcmp(dict->pairs[i].key, key, dict->key_s) == 0) {
      free(dict->pairs[i].key);
      free(dict->pairs[i].value);
      if (i + 1 < dict->count) {
        memmove(&dict->pairs[i], &dict->pairs[i + 1],
                (dict->count - i - 1) * sizeof(dict->pairs[0]));
      }
      dict->count--;
      return 0;
    }
  }
  return 1;
}

bool dict_tryget_value(dictionary *dict, void *key, void *out) {
  if (dict == NULL || key == NULL) {
    return false;
  }
  size_t key_hash = get_hash(key, dict->key_s);
  for (int i = 0; i < dict->count; i++) {
    if (dict->pairs[i].key_hash == key_hash &&
        memcmp(dict->pairs[i].key, key, dict->key_s) == 0) {
      memcpy(out, dict->pairs[i].value, dict->value_s);
      return true;
    }
  }
  return false;
}

bool dict_contains_key(dictionary *dict, void *key) {
  if (dict == NULL || key == NULL) {
    return false;
  }
  size_t key_hash = get_hash(key, dict->key_s);
  for (int i = 0; i < dict->count; i++) {
    if (dict->pairs[i].key_hash == key_hash &&
        memcmp(dict->pairs[i].key, key, dict->key_s) == 0) {
      return true;
    }
  }
  return false;
}

bool dict_contains_value(dictionary *dict, void *value) {
  if (dict == NULL || value == NULL) {
    return false;
  }
  size_t value_hash = get_hash(value, dict->value_s);
  for (int i = 0; i < dict->count; i++) {
    if (dict->pairs[i].value_hash == value_hash &&
        memcmp(dict->pairs[i].value, value, dict->value_s) == 0) {
      return true;
    }
  }
  return false;
}

int dict_clear(dictionary *dict) {
  if (dict == NULL) {
    return 1;
  }
  for (int i = 0; i < dict->count; i++) {
    free(dict->pairs[i].key);
    free(dict->pairs[i].value);
  }
  dict->count = 0;
  kv_pair *temp_pair_block =
      realloc(dict->pairs, sizeof(kv_pair) * INITIAL_CAP);
  if (temp_pair_block != NULL) {
    dict->pairs = temp_pair_block;
    dict->capacity = INITIAL_CAP;
  }
  return 0;
}

int free_dictionary(dictionary **d) {
  if (d == NULL || *d == NULL) {
    return 1;
  }
  dictionary *dict = *d;
  for (int i = 0; i < dict->count; i++) {
    free(dict->pairs[i].key);
    free(dict->pairs[i].value);
  }
  free(dict->pairs);
  free(dict);
  *d = NULL;
  return 0;
}

size_t dict_count(dictionary *dict) { return dict->count; }
