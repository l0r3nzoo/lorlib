#ifndef DIRECTORY_H
#define DIRECTORY_H

void dir_create(const char *name);
void dir_create_recursive(char *name);
void dir_list_files(char* directory_path,void (*file_handle)(char* file_path));

#endif
