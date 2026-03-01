
#include "diffiehellman.h"

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
