
#include "vernam.h"

VernamKey *vernam_init_key() {

  VernamKey *key = (VernamKey *)malloc(sizeof(VernamKey));

  if (!key) {
    perror("Error memory allocation!\n");
    exit(-1);
  }

  key->value = (uint8_t *)malloc(sizeof(uint8_t));

  if (!key->value) {
    perror("Error allocation memory!\n");
    exit(-1);
  }

  key->length = 1;

  return key;
}

void vernam_print_key(const VernamKey *key) {
  printf("[VernamKey]: addr: %p <- \"\x1b[96;1;11m%s\x1b[0m\" | "
         "length = %zu\n",
         &key->value, key->value, key->length);
}

void vernam_generate_key(VernamKey *key, const size_t key_length) {

  key->value = (uint8_t *)realloc(key->value, sizeof(uint8_t) * key_length);

  if (!key->value) {
    perror("Error allocation memory!\n");
    exit(-1);
  }

  key->length = key_length;

  for (size_t i = 0; i < key->length; i++) {

    for (size_t bit_idx = 0; bit_idx < sizeof(uint8_t) * 8;
         bit_idx++) { // 8 bit - size of uint8_t

      if (rand() % 2 == 1) { // generate 0 or 1 P~= 0,5
        key->value[i] =
            key->value[i] | (1 << bit_idx); // if generate 1 -> set 1
      } else {
        key->value[i] =
            key->value[i] & ~(1 << bit_idx); // if generate 0 -> clear (set 0)
      }
    }
  }
}

String *vernam_encryption(const String *message, const VernamKey *key) {

  if (key->length == message->length) {

    String *encrypted_message = init_string();

    for (size_t i = 0; i < message->length - 1; i++) { // ignore encryption /0
      string_add_char(encrypted_message, message->string[i] ^ key->value[i]);
    }

    return encrypted_message;

  } else {
    perror("Length don't match!\n");
    exit(-1);
  }
}

String *vernam_decryption(const String *encrypted_message,
                          const VernamKey *key) {

  if (key->length == encrypted_message->length) {

    String *decrypted_message = init_string();

    for (size_t i = 0; i < encrypted_message->length - 1;
         i++) { // ignore decryption /0
      string_add_char(decrypted_message,
                      encrypted_message->string[i] ^ key->value[i]);
    }

    return decrypted_message;

  } else {
    perror("Length don't match!\n");
    exit(-1);
  }
}

void vernam_free_key(VernamKey *key) {
  if (key) {
    key->length = 0;
    free(key->value);
    free(key);
  } else {
    perror("Key is empty!");
    exit(-1);
  }
}
