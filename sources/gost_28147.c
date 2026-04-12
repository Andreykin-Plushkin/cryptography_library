#include "gost_28147.h"

uint32_t f(uint32_t x, uint32_t key) {
  uint32_t sum = x + key;
  uint32_t res = 0;

  for (int i = 0; i < 8; i++) {
    uint8_t nibble = (sum >> (4 * i)) & 0xF;
    res |= ((uint32_t)SBOX[i][nibble]) << (4 * i);
  }

  return (res << 11) | (res >> (32 - 11));
}

void gost_encrypt_block(const uint8_t in[BLOCK_SIZE], uint8_t out[BLOCK_SIZE],
                        const gost_key_t *key) {

  uint32_t n1 = 0;
  uint32_t n2 = 0;

  for (size_t idx = 0; idx < 4; idx++) {
    n1 |= in[idx] << (4 - 1 - idx) * 8;
    n2 |= in[idx + 4] << (4 - 1 - idx) * 8;
  }

  // 1-24 K1..K8 K1..K8 K1..K8, 25-32 K8..K1
  for (int i = 0; i < 24; i++) {
    n2 ^= f(n1, key->k[i % 8]);
    n1 ^= f(n2, key->k[(i + 1) % 8]);
  }

  n1 = (in[0] << 24) | (in[1] << 16) | (in[2] << 8) | in[3];
  n2 = (in[4] << 24) | (in[5] << 16) | (in[6] << 8) | in[7];

  for (int i = 0; i < 32; i++) {
    uint32_t ki = (i < 24) ? key->k[i % 8] : key->k[7 - (i % 8)];
    uint32_t tmp = n1;
    n1 = n2 ^ f(n1, ki);
    n2 = tmp;
  }

  uint32_t t = n1;
  n1 = n2;
  n2 = t;

  for (size_t idx = 0; idx < 4; idx++) {
    out[idx] = n1 >> (4 - 1 - idx) * 8;
    out[idx + 4] = n2 >> (4 - 1 - idx) * 8;
  }
}

void gost_decrypt_block(const uint8_t in[BLOCK_SIZE], uint8_t out[BLOCK_SIZE],
                        const gost_key_t *key) {

  uint32_t n1 = 0;
  uint32_t n2 = 0;

  for (size_t idx = 0; idx < 4; idx++) {
    n1 |= in[idx] << (4 - 1 - idx) * 8;
    n2 |= in[idx + 4] << (4 - 1 - idx) * 8;
  }

  for (int i = 0; i < 32; i++) {
    uint32_t ki = (i < 8) ? key->k[i % 8] : key->k[7 - (i % 8)];
    uint32_t tmp = n1;
    n1 = n2 ^ f(n1, ki);
    n2 = tmp;
  }
  uint32_t t = n1;
  n1 = n2;
  n2 = t;

  for (size_t idx = 0; idx < 4; idx++) {
    out[idx] = n1 >> (4 - 1 - idx) * 8;
    out[idx + 4] = n2 >> (4 - 1 - idx) * 8;
  }
}

void gost_set_key(gost_key_t *key, const uint8_t key_bytes[KEY_SIZE]) {
  for (int i = 0; i < 8; i++)
    key->k[i] = (key_bytes[4 * i] << 24) | (key_bytes[4 * i + 1] << 16) |
                (key_bytes[4 * i + 2] << 8) | key_bytes[4 * i + 3];
}

void xor_block(uint8_t *dst, const uint8_t *a, const uint8_t *b) {
  for (int i = 0; i < BLOCK_SIZE; i++)
    dst[i] = a[i] ^ b[i];
}

// ECB
void gost_ecb_encrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key) {
  for (size_t i = 0; i < len; i += BLOCK_SIZE) {
    gost_encrypt_block(in + i, out + i, key);
  }
}
void gost_ecb_decrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key) {
  for (size_t i = 0; i < len; i += BLOCK_SIZE) {
    gost_decrypt_block(in + i, out + i, key);
  }
}

// CBC
void gost_cbc_encrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key, uint8_t iv[BLOCK_SIZE]) {
  uint8_t buf[BLOCK_SIZE];
  memcpy(buf, iv, BLOCK_SIZE);
  for (size_t i = 0; i < len; i += BLOCK_SIZE) {
    xor_block(buf, buf, in + i);
    gost_encrypt_block(buf, out + i, key);
    memcpy(buf, out + i, BLOCK_SIZE);
  }
}
void gost_cbc_decrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key, uint8_t iv[BLOCK_SIZE]) {
  uint8_t buf[BLOCK_SIZE], prev[BLOCK_SIZE];
  memcpy(prev, iv, BLOCK_SIZE);
  for (size_t i = 0; i < len; i += BLOCK_SIZE) {
    memcpy(buf, in + i, BLOCK_SIZE);
    gost_decrypt_block(in + i, out + i, key);
    xor_block(out + i, out + i, prev);
    memcpy(prev, buf, BLOCK_SIZE);
  }
}

// ---------- padding
size_t pkcs7_pad(uint8_t *data, size_t len) {
  size_t pad_len = BLOCK_SIZE - (len % BLOCK_SIZE);
  for (size_t i = 0; i < pad_len; i++)
    data[len + i] = (uint8_t)pad_len;
  return len + pad_len;
}
size_t pkcs7_unpad(uint8_t *data, size_t len) {
  if (len == 0)
    return 0;
  uint8_t pad = data[len - 1];
  if (pad == 0 || pad > BLOCK_SIZE)
    return len; // ошибка
  for (size_t i = 0; i < pad; i++)
    if (data[len - 1 - i] != pad)
      return len;
  return len - pad;
}
