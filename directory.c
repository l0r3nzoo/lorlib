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

void dir_create_recursive(const char* name){

}
