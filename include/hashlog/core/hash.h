#ifndef HASHLOG_HASH_H
#define HASHLOG_HASH_H

#include <stdlib.h>
#include <openssl/evp.h>

#define SHA256_SIZE 64

/**
 * @brief size of a hash text used in the current version of hash creation
 * 
 */
#define HASH_HEX_SIZE 2 * SHA256_SIZE + 1

int create_hash(char** buffer, size_t length, unsigned char** digest, unsigned int *digest_len);

void bytes_to_hex(const unsigned char* bytes, size_t len, char* hex);

#endif