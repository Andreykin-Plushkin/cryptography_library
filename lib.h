
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LIB_H_

#define LIB_H_

typedef struct {
  int64_t g;
  int64_t x;
  int64_t y;
} EuclidVector; // g = ax + by

typedef struct {
  int64_t p;
  int64_t g;
  int64_t public_key;
  int64_t private_key;
  int64_t shared_secret;
} DiffieHellmanStruct;

typedef struct {
  int64_t p;
  int64_t c;
  int64_t d; // cd mod (p-1) = 1
} ShamirStruct;

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

void Shamir_init(ShamirStruct *object, int64_t p,
                 int64_t c); // init ShamirStruct

void Shamir_print_struct(ShamirStruct object);

uint64_t mod_exp(int64_t base, int64_t exp,
                 int64_t m); // | (base^exp) (mod m) right-to-left
uint64_t gcd(int a, int b);  // Euclidean alogitm GCD(a, b)

EuclidVector *
gcd_extended(int64_t a, int64_t b,
             EuclidVector *vector); // Euclidean extended algorithm

void EuclidVector_print(EuclidVector vector);

void DiffieHellman_init(DiffieHellmanStruct *object, int64_t p, int64_t g);
void DiffieHellman_print_object(DiffieHellmanStruct object);
void DiffieHellman_generate_private_key(DiffieHellmanStruct *object);

#endif
