
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
