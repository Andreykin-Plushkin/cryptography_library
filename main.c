
#include "lib.h"

#include <stdint.h>
#include <stdio.h>

void test_mod_exp();
void test_gcd();
void test_gcd_extended();
void test_DiffieHellman();
void test_Shamir();
void test_Elgamal();
void test_rsa();
void test_vernam();

#define SIZE_BUFFER 10

int main() {

  srand(time(NULL));

  // test_mod_exp();
  // test_gcd();
  // test_gcd_extended();
  // test_DiffieHellman();
  // test_Shamir();
  // test_Elgamal();
  // test_rsa();

  test_vernam();

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

void test_Shamir() {

  int64_t p = 23;

  int64_t m = 10;

  ShamirStruct A, B;

  Shamir_init(&A, p, 7);
  Shamir_init(&B, p, 5);

  Shamir_print_struct(A);
  Shamir_print_struct(B);

  assert((m < p) && "[ERROR] m > p");

  int64_t x1 = mod_exp(m, A.c, A.p);
  int64_t x2 = mod_exp(x1, B.c, B.p);
  int64_t x3 = mod_exp(x2, A.d, A.p);
  int64_t x4 = mod_exp(x3, B.d, B.p);

  printf("x1 = (%ld^%ld mod %ld) = %ld\n", m, A.c, A.p, x1);
  printf("x2 = (%ld^%ld mod %ld) = %ld\n", x1, B.c, B.p, x2);
  printf("x3 = (%ld^%ld mod %ld) = %ld\n", x2, A.d, A.p, x3);
  printf("x4 = (%ld^%ld mod %ld) = %ld\n", x3, B.d, B.p, x4);

  if (x4 == m) {
    printf("\t==> x4 == m | %ld == %ld\n", x4, m);
  }
}

void test_Elgamal() {

  uint64_t p = 23;
  uint64_t g = 5;
  uint64_t m = 15;

  ElgamalStruct A, B;

  Elgamal_init(&A, p, g);
  Elgamal_init(&B, p, g);

  Elgamal_print_struct(A);
  Elgamal_print_struct(B);

  ElgamalMessageStruct message;

  Elgamal_make_message(A, B.d, m, &message);

  Elgamal_print_message(message);

  printf("Decrypting message...\n");

  uint64_t decrypted_message = Elgamal_message_decrypt(B, message);

  printf("Decrypted message = (%ld)\n", decrypted_message);

  if (m == decrypted_message) {
    printf("m == decrypted_message | (%ld) == (%ld)\n", m, decrypted_message);
  }
}

void test_rsa() {

  int16_t p;
  int16_t q;

  RsaStruct A, B;

  char message[SIZE_BUFFER];

  uint64_t encrypted_message[SIZE_BUFFER];

  for (size_t i = 0; i < SIZE_BUFFER; i++) {
    encrypted_message[i] = 0;
  }

  char decrypted_message[SIZE_BUFFER];

  printf("Write p and q:");
  scanf("%hd %hd", &p, &q);

  printf("Write message (Max length = %d):", SIZE_BUFFER - 1);
  scanf("%s", message);

  RsaStruct_init(p, q, &A);
  RsaStruct_init(p, q, &B);

  RsaStruct_print(A);
  RsaStruct_print(B);

  RsaOpenKeyStruct open_key_A;

  open_key_A.n = A.n;
  open_key_A.e = A.e;

  printf("----- Crypt Message -----\n");
  rsa_crypt_message(open_key_A, message, encrypted_message, SIZE_BUFFER);
  printf("-------------------------\n");

  printf("----- Decrypt message -----\n");
  rsa_decrypt_message(B, encrypted_message, decrypted_message, SIZE_BUFFER);
  printf("---------------------------\n");

  printf("[Decrypt message] '%s'\n", decrypted_message);
}

void test_vernam() {

  String *text = init_string();

  printf("Write string:");
  input_string(text);

  print_string(text);

  free_string(text);
}
