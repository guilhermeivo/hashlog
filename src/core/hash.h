#ifndef HASHLOG_HASH_H
#define HASHLOG_HASH_H

#include <stdlib.h>
#include <openssl/evp.h>

#define SHA256_SIZE 64

int create_hash(char** buffer, size_t length, unsigned char** digest, unsigned int *digest_len);

void bytes_to_hex(const unsigned char* bytes, size_t len, char* hex);

#endif