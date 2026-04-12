
#ifndef STRINGS_H_

#define STRINGS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t *string;
  size_t length;
} String;

String *init_string();

void string_add_char(String *str, char symbol);
void extend_size_string(String *str, size_t additional_size);

void input_string(String *str);

void free_string(String *str);

#endif
