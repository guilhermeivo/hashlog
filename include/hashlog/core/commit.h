#ifndef HASHLOG_COMMIT_H
#define HASHLOG_COMMIT_H

#include <hashlog/core/object.h>
#include <hashlog/core/config.h>

#define MAX_SIZE_COMMIT 4096

int create_commit(
    const char* blob_hex,
    const char* parent_hex,
    const char* author,
    char hex[2 * SHA256_SIZE + 1]
);

#endif