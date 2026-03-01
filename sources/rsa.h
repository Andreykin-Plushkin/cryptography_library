
#include <assert.h>
#include <stdint.h>

#include "arithmetic.h"

#ifndef RSA_H_

#define RSA_H_

typedef struct {

  uint16_t p;
  uint16_t q;
  uint64_t n; // N = p * q
  uint64_t e; // (e, n) - open key
  uint64_t d; // (d, n) - secret key

} RsaStruct;

typedef struct {
  uint64_t e;
  uint64_t n;
} RsaOpenKeyStruct;

typedef struct {
  uint64_t d;
  uint64_t n;
} RsaSecretKeyStruct;

void RsaStruct_init(int16_t p, int16_t q, RsaStruct *object);

void RsaStruct_print(RsaStruct object);

void rsa_crypt_message(RsaOpenKeyStruct object, char *message,
                       uint64_t *out_message, size_t buffer_size);

void rsa_decrypt_message(RsaStruct object, uint64_t *encrypted_message,
                         char *out_message, size_t buffer_size);

#endif
