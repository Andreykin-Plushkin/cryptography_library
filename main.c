
#include "lib.h"

#include <stdio.h>

void test_mod_exp();
void test_gcd();
void test_gcd_extended();
void test_DiffieHellman();

int main() {

  srand(time(NULL));

  test_mod_exp();
  test_gcd();
  test_gcd_extended();
  test_DiffieHellman();

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

void test_DiffieHellman() {

  int64_t p = 179424673;
  int64_t g = 2;

  DiffieHellmanStruct A, B;

  DiffieHellman_init(&A, p, g);
  DiffieHellman_init(&B, p, g);

  DiffieHellman_print_object(A);
  DiffieHellman_print_object(B);

  printf("-- Sharing public keys --\n");

  A.shared_secret = mod_exp(B.public_key, A.private_key, A.p);
  B.shared_secret = mod_exp(A.public_key, B.private_key, B.p);

  if (A.shared_secret == B.shared_secret) {
    printf("Shared secret equals!\n");
  }

  DiffieHellman_print_object(A);
  DiffieHellman_print_object(B);
}
