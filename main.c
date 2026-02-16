
#include "lib.h"

#include <stdio.h>

void test_mod_exp();
void test_gcd();
void test_gcd_extended();

int main() {

  test_mod_exp();
  test_gcd();
  test_gcd_extended();

  return 0;
}

void test_mod_exp() {

  int base, exp, m;

  printf("Write base:");
  scanf("%d", &base);

  printf("Write exp:");
  scanf("%d", &exp);

  printf("Write mod:");
  scanf("%d", &m);

  uint64_t result = mod_exp(base, exp, m);

  printf("[x^a mod p] result: %lu\n", result);
}

void test_gcd() {

  int a, b;

  printf("Write a:");
  scanf("%d", &a);

  printf("Write b:");
  scanf("%d", &b);

  printf("[GCD] result: %lu\n", gcd(a, b));
}

void test_gcd_extended() {

  int a, b;

  printf("Write a:");
  scanf("%d", &a);

  printf("Write b:");
  scanf("%d", &b);

  EuclidVector temp;
  gcd_extended(a, b, &temp);

  EuclidVector_print(temp);
}
