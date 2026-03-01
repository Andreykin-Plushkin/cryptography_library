
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#ifndef ARITHMETIC_H_

#define ARITHMETIC_H_

typedef struct {
  int64_t g;
  int64_t x;
  int64_t y;
} EuclidVector; // g = ax + by

uint64_t gcd(int a, int b);
uint64_t mod_exp(int64_t base, int64_t exp, int64_t m);

EuclidVector *gcd_extended(int64_t a, int64_t b, EuclidVector *vector);
void EuclidVector_print(EuclidVector vector);

#endif
