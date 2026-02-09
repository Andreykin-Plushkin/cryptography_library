#include "lib.h"


uint64_t mod_exp(int base, int exp, int m) {

  assert((base > 0 && exp > 0 && m > 0) && "Numbers don't should be negative!");

  uint64_t result = 1;
  uint64_t temp   = base % m;

  while (exp != 0) {

    if ((exp & 1) == 1) {
      result = (result * temp) % m;
    }

    temp = (temp * temp) % m;
    exp = exp >> 1;
  }

  return result;
}

uint64_t gcd(int a, int b) {

  assert((a > 0 && b > 0) && "Numbers don't should be negative!");

  while (a != 0 && b != 0) {
    if (a > b)  { a = a % b; }
    else        { b = b % a; }
  }

  return (uint64_t)(a + b);
}
