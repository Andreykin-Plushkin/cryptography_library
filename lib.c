#include "lib.h"


uint64_t mod_exp(int base, int exp, int m) {

  assert((base >= 0 && exp>= 0 && m >= 0) && "Numbers don't should be negative!");

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
