#ifndef DIRECTORY_H
#define DIRECTORY_H

void dir_create(const char *name);
void dir_create_recursive(char *name);
void dir_list_files(char* directory_path,void (*file_handle)(char* file_path));
void dir_remove(const char* name);
#ifdef _WIN32
void dir_rename(const unsigned short* source,const unsigned short* destination);
#else
#endif
void dir_rename(const char* source,const char* destination);
#endif
