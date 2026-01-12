#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>
#define PATH_SEPARATOR "\\"
#define stat _stat
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define rmdir _rmdir
#else
#include <dirent.h>
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

int dir_create(const char *name) {
#ifdef _WIN32
  return _mkdir(name);
#else
  return mkdir(name, 0755);
#endif
}

int dir_create_recursive(char *name) {
  char buffer[1024] = "";
  char *path = strtok(name, "/\\");

  while (path != NULL) {
    if (buffer[0] != '\0') {
      strcat(buffer, PATH_SEPARATOR);
    }
    strcat(buffer, path);
    if (dir_create(buffer) != 0) {
      return 1;
    }
    path = strtok(NULL, "/\\");
  }
  return 0;
}

void dir_list_files(char *directory_path,
                    void (*file_handle)(char *file_path)) {
#ifdef _WIN32
  WIN32_FIND_DATAA findData;
  HANDLE hFind;
  char search_path[1024];

  snprintf(search_path, sizeof(search_path), "%s\\*", directory_path);
  hFind = FindFirstFileA(search_path, &findData);

  if (hFind == INVALID_HANDLE_VALUE) {
    return;
  }

  do {
    if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
      char file_path[1024];
      snprintf(file_path, sizeof(file_path), "%s\\%s", directory_path,
               findData.cFileName);
      file_handle(file_path);
    }
  } while (FindNextFileA(hFind, &findData) != 0);

  FindClose(hFind);
#else
  DIR *direct = opendir(directory_path);
  if (direct == NULL) {
    return;
  }

  struct dirent *infile;
  while ((infile = readdir(direct))) {
    if (strcmp(infile->d_name, ".") == 0 || strcmp(infile->d_name, "..") == 0) {
      continue;
    }

    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", directory_path,
             infile->d_name);

    struct stat buffer;
    if (stat(file_path, &buffer) == 0 && S_ISREG(buffer.st_mode)) {
      file_handle(file_path);
    }
  }
  closedir(direct);
#endif
}

int dir_remove(const char *name) { return rmdir(name); }

#ifdef _WIN32
int dir_rename(const unsigned short *source,
               const unsigned short *destination) {

  return MoveFileW(source, destination);
}
#else
int dir_rename(const char *source, const char *destination) {

  return rename(source, destination);
}
#endif

int dir_exists(const char *name) {
#ifdef _WIN32
  if (_access(name, 0) == 0) {
    struct stat st;
    stat(name, &st);
    return (st.st_mode * S_IFDIR) != 0;
  }
#else
  struct stat st;
  if (stat(name, &st) == 0) {
    return S_ISDIR(st.st_mode);
  }
#endif
  return 0;
}
