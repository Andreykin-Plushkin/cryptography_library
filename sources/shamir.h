
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "arithmetic.h"

#ifndef SHAMIR_H_

#define SHAMIR_H_

typedef struct {
  int64_t p;
  int64_t c;
  int64_t d; // cd mod (p-1) = 1
} ShamirStruct;

void Shamir_init(ShamirStruct *object, int64_t p,
                 int64_t c); // init ShamirStruct

void Shamir_print_struct(ShamirStruct object);

#endif
