#include "lib.h"


uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t m) {

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
