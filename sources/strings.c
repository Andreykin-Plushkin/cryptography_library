
#include "strings.h"

String *init_string() {

  String *str = (String *)malloc(sizeof(String));

  if (!str) {
    perror("Error memory allocation!\n");
    exit(-1);
  }

  str->string = (uint8_t *)malloc(sizeof(uint8_t));

  if (!str->string) {
    perror("Error memory allocation!\n");
    exit(-1);
  }

  str->string[0] = '\0';
  str->length = 1;

  return str;
}

void input_string(String *str) {

  int c = 0;

  while ((c = getchar()) != '\n') {
    string_add_char(str, c);
  }
}

void string_add_char(String *str, char symbol) {

  str->string = (uint8_t *)realloc(str->string, str->length + 1);

  if (!str->string) {
    perror("Error memory allocation!\n");
    exit(-1);
  }

  str->string[str->length - 1] = (uint8_t)symbol;
  str->string[str->length] = '\0';

  str->length = str->length + 1;
}

void extend_size_string(String *str, size_t additional_size) {
  if (str == NULL || str->string == NULL)
    return;

  str->string = (uint8_t *)realloc(str->string, str->length + additional_size);

  if (!str->string) {
    perror("Error realloc in extend_size_string!\n");
    exit(-1);
  }

  str->length = str->length + additional_size;
}

void free_string(String *str) {

  str->length = 0;

  free(str->string);
  free(str);
}
