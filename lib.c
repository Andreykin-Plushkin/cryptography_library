#include "lib.h"

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

void DiffieHellman_generate_private_key(DiffieHellmanStruct *object) {
  object->private_key = (int64_t)((rand() % (object->p - 2)) + 1);
}

void DiffieHellman_init(DiffieHellmanStruct *object, int64_t p, int64_t g) {

  assert((p > 0 && g > 0) && "p and g should be > 0!");
  assert((mod_exp(g, (p - 1) / 2, p)) && "g is not primitive root modulo p");

  object->p = p;
  object->g = g;
  object->shared_secret = 0;

  DiffieHellman_generate_private_key(object);

  object->public_key = mod_exp(object->g, object->private_key, object->p);
}

void DiffieHellman_print_object(DiffieHellmanStruct object) {
  printf("DiffieHellman object: \n  | g = %ld\n  | p = %ld\n  | public_key = "
         "%ld\n  | private_key = %ld\n  | shared_secret = %ld\n",
         object.g, object.p, object.public_key, object.private_key,
         object.shared_secret);
}

void Shamir_init(ShamirStruct *object, int64_t p, int64_t c) {
  
  assert((p > 0 && c > 0) && "[ERROR] p | g < 0");
  assert((gcd(c, p-1) == 1) && "[ERROR] gcd(c, p-1) != 1");

  EuclidVector vector;
  gcd_extended(c, p-1, &vector); // c*(x) + (p-1)*(y) = g 

  object->p = p;
  object->c = c;
  object->d = (vector.x > 0) ? vector.x : (vector.x + (p-1));

}

void Shamir_print_struct(ShamirStruct object) {
  printf("ShamirStruct -> [ p = (%ld) | c = (%ld) | d = (%ld) ]\n", object.p, object.c, object.d);
}


void Elgamal_init(ElgamalStruct *object, int64_t p, int64_t g) {

  assert((p > 0 && g > 0) && "[ERROR] p | g < 0");
  assert((mod_exp(g, (p - 1) / 2, p)) && "g is not primitive root modulo p");

  object->p = p;
  object->g = g;
  object->k = (int64_t)(rand() % (p-2) + 1); // k c [1; p-2]
  object->c = (int64_t)(rand() % (p-1) + 1); // c c [1; p-1]
  object->d = mod_exp(object->g, object->c, object->p);

}

void Elgamal_make_message(ElgamalStruct object, uint64_t d, uint64_t m, ElgamalMessageStruct *message) {
  message->r = mod_exp(object.g, object.k, object.p);
  message->e = ((m % object.p) * mod_exp(d, object.k, object.p)) % object.p; 
}

uint64_t Elgamal_message_decrypt(ElgamalStruct object, ElgamalMessageStruct message) {
  uint64_t m = ((message.e % object.p) * (mod_exp(message.r, object.p - 1 - object.c, object.p))) % object.p; // e * r^(p-1-c) mod p
  return m;
}

void Elgamal_print_struct(ElgamalStruct object) {
  printf("ElgamalStruct: \n\t p = (%ld) | g = (%ld) \n\t k = (%ld) | c = (%ld) \n\t d = (%ld)\n", object.p, object.g, object.k, object.c, object.d);
}

void Elgamal_print_message(ElgamalMessageStruct message) {
  printf("ElgamalMessageStruct: \n\tr,e = (%ld) (%ld)\n", message.r, message.e);
}

