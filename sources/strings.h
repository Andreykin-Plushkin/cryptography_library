
#include <stdio.h>
#include <stdlib.h>

#ifndef STRINGS_H_

#define STRINGS_H_

typedef struct {
  char *string;
  size_t length;
} String;

String *init_string();

void string_add_char(String *str, char symbol);

void input_string(String *str);

void print_string(const String *str);

void free_string(String *str);

#endif
