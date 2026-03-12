
#ifndef VERNAM_H_

#define VERNAM_H_

#include <stdint.h>
#include <stdlib.h>

#include "strings.h"

typedef struct {
  uint8_t *value; // uint8_t (1 byte) XOR char (1 byte)
  size_t length;
} VernamKey;

VernamKey *vernam_init_key(); // first allocation memory for key

void vernam_generate_key(
    VernamKey *key,
    const size_t key_length); // reallocation memory and generate key

void vernam_print_key(const VernamKey *key);

String *vernam_encryption(const String *message, const VernamKey *key);
String *vernam_decryption(const String *encrypted_message,
                          const VernamKey *key);

void vernam_free_key(VernamKey *key);

#endif
