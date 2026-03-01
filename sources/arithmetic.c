
#include "arithmetic.h"

int isPrime(int64_t number) { // poor implementation

  for (int64_t i = 2; i < number / 2; i++) {
    if (number % i == 0) {
      return 0;
    }
  }
  return 1;
}

uint64_t mod_exp(int64_t base, int64_t exp, int64_t m) {

  assert((base > 0 && exp > 0 && m > 0) && "Numbers don't should be negative!");

  uint64_t result = 1;
  uint64_t temp = base % m;

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
    if (a > b) {
      a = a % b;
    } else {
      b = b % a;
    }
  }

  return (uint64_t)(a + b);
}

EuclidVector *gcd_extended(int64_t a, int64_t b, EuclidVector *vector) {

  assert((a >= 0 && b >= 0) && "Numbers don't should be negative!");

  if (b == 0) {
    vector->g = a;
    vector->x = 1;
    vector->y = 0;
    return vector;
  }

  EuclidVector temp;
  gcd_extended(b, a % b, &temp);

  vector->g = temp.g;
  vector->x = temp.y;
  vector->y = temp.x - (a / b) * temp.y;

  return vector;
}

void EuclidVector_print(EuclidVector vector) {
  printf("EuclidVector (%ld %ld %ld)\n", vector.g, vector.x, vector.y);
}
