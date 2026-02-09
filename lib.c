#include "lib.h"


uint64_t mod_exp(int base, int exp, int m) {

  uint64_t result = 1;
  uint64_t temp   = base % m;

  if (base <= 0 || exp <= 0 || m <= 0) {
    perror("Numbers don't should be negative!");
    return -1;
  }

  while (exp != 0) {

    if ((exp & 1) == 1) {
      result = (result * temp) % m;
    }

    temp = (temp * temp) % m;
    exp = exp >> 1;
  }

  return result;
}
