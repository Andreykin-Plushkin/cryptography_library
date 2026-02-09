
#include <stdio.h>
#include <assert.h>
#include <stdint.h>


#ifndef LIB_H_

#define LIB_H_

uint64_t mod_exp(int base, int exp, int m); // | (base^exp) (mod m) right-to-left 
uint64_t gcd(int a, int b); // Euclidean alogitm GCD(a, b)


#endif
