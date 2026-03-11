
#include "strings.h"

String *init_string() {

  String *str = (String *)malloc(sizeof(String));

  if (!str) {
    perror("Error memory allocation!\n");
    exit(-1);
  }

  str->string = (char *)malloc(sizeof(char *));

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

  str->string = (char *)realloc(str->string, str->length + 1);

  if (!str->string) {
    perror("Error memory allocation!\n");
    exit(-1);
  }

  str->string[str->length - 1] = symbol;
  str->string[str->length] = '\0';

  str->length = str->length + 1;
}

void print_string(const String *str) {

  for (size_t i = 0; str->string[i] != '\0'; i++) {
    printf("addr: %p <- %c\n", &(str->string[i]), str->string[i]);
  }
}

void free_string(String *str) {

  str->length = 0;

  free(str->string);
  free(str);
}
