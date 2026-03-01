
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arithmetic.h"

#ifndef ELGAMAL_H_

#define ELGAMAL_H_

typedef struct {
  int64_t p;
  int64_t g; // primitive root
  int64_t k; // session key (1 < k < p - 2)
  int64_t c; // (1 < c < p - 1)
  int64_t d; // g^c mod p
} ElgamalStruct;

typedef struct {
  int64_t r; // g^k mod p
  int64_t e; // m*(d^k) mod p
} ElgamalMessageStruct;

void Elgamal_init(ElgamalStruct *object, int64_t p, int64_t g);
void Elgamal_make_message(ElgamalStruct object, uint64_t d, uint64_t m,
                          ElgamalMessageStruct *message);
uint64_t Elgamal_message_decrypt(ElgamalStruct object,
                                 ElgamalMessageStruct message);
void Elgamal_print_struct(ElgamalStruct object);
void Elgamal_print_message(ElgamalMessageStruct message);

#endif
