
#include "file_operations.h"

void read_file_to_string(const char *filename, String *buffer) {

  FILE *file = NULL;
  size_t file_size = 0;

  file = fopen(filename, "rb");

  if (file == NULL) {
    perror("file doesn't exist!\n");
    exit(-1);
  }

  if (buffer != NULL) {

    fseek(file, 0, SEEK_END);
    file_size = ftell(file) - 1;
    rewind(file);

    extend_size_string(buffer, file_size);

    size_t bytes_read = fread(buffer->string, 1, file_size, file);

    if (bytes_read != file_size) {
      perror("Error reading file!\n");
      free_string(buffer);
      fclose(file);
      exit(-1);
    } else {
      buffer->string[buffer->length] = '\0';
    }
  }
  fclose(file);
}
