
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arithmetic.h"

#ifndef DIFFIEHELLMAN_H_

#define DIFFIEHELLMAN_H_

typedef struct {
  int64_t p;
  int64_t g;
  int64_t public_key;
  int64_t private_key;
  int64_t shared_secret;
} DiffieHellmanStruct;

void DiffieHellman_init(DiffieHellmanStruct *object, int64_t p, int64_t g);
void DiffieHellman_print_object(DiffieHellmanStruct object);
void DiffieHellman_generate_private_key(DiffieHellmanStruct *object);

#endif
