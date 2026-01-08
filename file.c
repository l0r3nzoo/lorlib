#include "file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#endif
#include <sys/stat.h>

int file_create(const char *file_name) {
  FILE *file = fopen(file_name, "w");
  if (file == NULL) {
    return 1;
  } else {
    fclose(file);
    return 0;
  }
}

int file_delete(const char *file_name) { return remove(file_name); }

int file_copy(const char *source_filename, const char *destination_filename) {
  FILE *s_file = fopen(source_filename, "rb");
  if (!s_file)
    return 1;

  FILE *d_file = fopen(destination_filename, "wb");
  if (!d_file) {
    fclose(s_file);
    return 1;
  }

  unsigned char buffer[4096];
  size_t bytes_read;

  while ((bytes_read = fread(buffer, 1, sizeof buffer, s_file)) > 0) {
    if (fwrite(buffer, 1, bytes_read, d_file) != bytes_read) {
      fclose(s_file);
      fclose(d_file);
      return 1;
    }
  }

  if (ferror(s_file)) {
    fclose(s_file);
    fclose(d_file);
    return 1;
  }

  fclose(s_file);
  fclose(d_file);
  return 0;
}
int file_move(const char *source_filename, const char *destination_filename) {
  if (rename(source_filename, destination_filename) == 0) {
    return 0;
  }
  if (file_copy(source_filename, destination_filename) != 0) {
    return 1;
  }
  if (remove(source_filename) != 0) {
    return 1;
  }
  return 0;
}

bool file_exists(const char *file_name) {
  FILE *file = fopen(file_name, "rb");
  if (file != NULL) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

int file_append_text(const char *file_name, const char *content) {
  FILE *file = fopen(file_name, "ab");
  if (file == NULL) {
    return 1;
  }
  size_t content_size = strlen(content);
  size_t written = fwrite(content, 1, content_size, file);
  if (written != content_size) {
    fclose(file);
    return 1;
  }
  if (fclose(file) != 0) {
    return 1;
  }
  return 0;
}

char *file_read_text(const char *file_name) {
  FILE *file = fopen(file_name, "rb");
  if (!file)
    return NULL;

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return NULL;
  }

  long file_size = ftell(file);
  if (file_size < 0) {
    fclose(file);
    return NULL;
  }

  rewind(file);

  char *buffer = malloc(file_size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  size_t read_size = fread(buffer, 1, file_size, file);
  fclose(file);

  if (read_size != (size_t)file_size) {
    free(buffer);
    return NULL;
  }

  buffer[file_size] = '\0';
  return buffer;
}
