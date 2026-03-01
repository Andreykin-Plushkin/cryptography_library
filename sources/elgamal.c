
#include "elgamal.h"

void Elgamal_init(ElgamalStruct *object, int64_t p, int64_t g) {

  assert((p > 0 && g > 0) && "[ERROR] p | g < 0");
  assert((mod_exp(g, (p - 1) / 2, p)) && "g is not primitive root modulo p");

  object->p = p;
  object->g = g;
  object->k = (int64_t)(rand() % (p - 2) + 1); // k c [1; p-2]
  object->c = (int64_t)(rand() % (p - 1) + 1); // c c [1; p-1]
  object->d = mod_exp(object->g, object->c, object->p);
}

void Elgamal_make_message(ElgamalStruct object, uint64_t d, uint64_t m,
                          ElgamalMessageStruct *message) {
  message->r = mod_exp(object.g, object.k, object.p);
  message->e = ((m % object.p) * mod_exp(d, object.k, object.p)) % object.p;
}

uint64_t Elgamal_message_decrypt(ElgamalStruct object,
                                 ElgamalMessageStruct message) {
  uint64_t m = ((message.e % object.p) *
                (mod_exp(message.r, object.p - 1 - object.c, object.p))) %
               object.p; // e * r^(p-1-c) mod p
  return m;
}

void Elgamal_print_struct(ElgamalStruct object) {
  printf("ElgamalStruct: \n\t p = (%ld) | g = (%ld) \n\t k = (%ld) | c = (%ld) "
         "\n\t d = (%ld)\n",
         object.p, object.g, object.k, object.c, object.d);
}

void Elgamal_print_message(ElgamalMessageStruct message) {
  printf("ElgamalMessageStruct: \n\tr,e = (%ld) (%ld)\n", message.r, message.e);
}
