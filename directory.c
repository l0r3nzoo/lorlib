#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif
#include <sys/stat.h>

void dir_create(const char *name) {
#ifdef __linux__
  mkdir(name, 0755);
#else
  _mkdir(name);
#endif
}

void dir_create_recursive(char *name) {
  char *path = strtok(name, "/\\");
  char buffer[1024]="";
  while (path != NULL) {
    strcat(buffer, path);
    dir_create(buffer);
    strcat(buffer, "/");
    path = strtok(NULL, "/\\");
  }
}
