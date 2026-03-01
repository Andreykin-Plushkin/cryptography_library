
#include "rsa.h"

void RsaStruct_init(int16_t p, int16_t q, RsaStruct *object) {

  assert((p != q) && "[ERROR] p == q");
  assert((p > 0 && q > 0) && "[ERROR] p < 0 | q < 0");
  assert((isPrime(p) && isPrime(q)) && "[ERROR] p | q isn't prime");

  EuclidVector vector;

  uint64_t phi = (p - 1) * (q - 1);

  object->p = p;
  object->q = q;
  object->n = p * q;

  for (int64_t e = phi - 2; e > 2; e--) {
    if (gcd(e, phi) == 1 && isPrime(e) == 1) { // e & phi (p-1)(q-1) - prime
      object->e = e;
      break;
    }
  }

  gcd_extended(object->e, phi, &vector); // e*(x) + phi*(y) = g

  object->d = (vector.x > 0) ? (uint64_t)vector.x : (vector.x + phi);
}

void RsaStruct_print(RsaStruct object) {
  printf("[RsaStruct]\n");
  printf("\tN = %ld > p = %hd | q = %hd\n", object.n, object.p, object.q);
  printf("\tphi = %d\n", (object.p - 1) * (object.q - 1));
  printf("\te = %ld | d = %ld\n", object.e, object.d);
}

void rsa_crypt_message(RsaOpenKeyStruct key, char *message,
                       uint64_t *out_message, size_t buffer_size) {

  for (size_t i = 0; i < buffer_size - 2; i++) {
    if (message[i] != '\0' && message[i] != '\n') {
      out_message[i] = mod_exp((int64_t)message[i], key.e, key.n);
      printf("'%c'(%d) -> (%ld)\n", message[i], message[i], out_message[i]);
    } else {
      break;
    }
  }
}

void rsa_decrypt_message(RsaStruct object, uint64_t *encrypted_message,
                         char *out_message, size_t buffer_size) {

  for (size_t i = 0; i < buffer_size - 2; i++) {
    if (encrypted_message[i] != 0) {
      out_message[i] =
          mod_exp((int64_t)encrypted_message[i], object.d, object.n);
      printf("(%ld) -> '%c'(%d)\n", encrypted_message[i], out_message[i],
             out_message[i]);
    } else {
      break;
    }
  }
}
