
#ifndef GOST_28147_H_

#define GOST_28147_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8 // 64 бита
#define KEY_SIZE 32  // 256 бит

// Тестовый S-блок (RFC 4357, id-Gost28147-89-TestParamSet)
static const uint8_t SBOX[8][16] = {
    {4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3},
    {14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9},
    {5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11},
    {7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3},
    {6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 3, 0, 11, 14, 2},
    {4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14},
    {13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12},
    {1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12}};

// 8x32 KZU
typedef struct {
  uint32_t k[8];
} gost_key_t;

uint32_t f(uint32_t x, uint32_t key);

void gost_encrypt_block(const uint8_t in[BLOCK_SIZE], uint8_t out[BLOCK_SIZE],
                        const gost_key_t *key);

void gost_decrypt_block(const uint8_t in[BLOCK_SIZE], uint8_t out[BLOCK_SIZE],
                        const gost_key_t *key);

void gost_set_key(gost_key_t *key, const uint8_t key_bytes[KEY_SIZE]);

void xor_block(uint8_t *dst, const uint8_t *a, const uint8_t *b);

// ECB
void gost_ecb_encrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key);

void gost_ecb_decrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key);

// CBC
void gost_cbc_encrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key, uint8_t iv[BLOCK_SIZE]);

void gost_cbc_decrypt(const uint8_t *in, uint8_t *out, size_t len,
                      const gost_key_t *key, uint8_t iv[BLOCK_SIZE]);

// ---------- padding ------------
size_t pkcs7_pad(uint8_t *data, size_t len);
size_t pkcs7_unpad(uint8_t *data, size_t len);
// -------------------------------

#endif
