
#include "shamir.h"

void Shamir_init(ShamirStruct *object, int64_t p, int64_t c) {

  assert((p > 0 && c > 0) && "[ERROR] p | g < 0");
  assert((gcd(c, p - 1) == 1) && "[ERROR] gcd(c, p-1) != 1");

  EuclidVector vector;
  gcd_extended(c, p - 1, &vector); // c*(x) + (p-1)*(y) = g

  object->p = p;
  object->c = c;
  object->d = (vector.x > 0) ? vector.x : (vector.x + (p - 1));
}

void Shamir_print_struct(ShamirStruct object) {
  printf("ShamirStruct -> [ p = (%ld) | c = (%ld) | d = (%ld) ]\n", object.p,
         object.c, object.d);
}
