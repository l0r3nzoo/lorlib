#include <stdbool.h>
#ifndef DIRECTORY_H
#define DIRECTORY_H

int dir_create(const char *name);
int dir_create_recursive(char *name);
void dir_list_files(char *directory_path, void (*file_handle)(char *file_path));
int dir_remove(const char *name);
#ifdef _WIN32
int dir_rename(const unsigned short *source, const unsigned short *destination);
#else
int dir_rename(const char *source, const char *destination);
#endif

int dir_exists(const char *name);
#endif
