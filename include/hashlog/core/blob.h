#ifndef HASHLOG_BLOB_H
#define HASHLOG_BLOB_H

#include <hashlog/core/object.h>

int create_blob(char* text, size_t size, char hex[2 * SHA256_SIZE + 1]);

#endif