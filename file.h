#ifndef FILE_H
#define FILE_H
#include <stdbool.h>

int file_create(const char *file_name);
int file_delete(const char *file_name);

int file_copy(const char *source_filename, const char *destination_filename);
int file_move(const char *source_filename, const char *destination_filename);

bool file_exists(const char *file_name);

int file_append_text(const char *file_name, const char *content);
char *file_read_text(const char *file_name);

#endif
