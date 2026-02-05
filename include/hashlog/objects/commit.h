#ifndef HASHLOG_COMMIT_H
#define HASHLOG_COMMIT_H

#include <string.h>

#include <hashlog/core/object.h>
#include <hashlog/core/config.h>

#define MAX_SIZE_COMMIT 4096

typedef struct {
    char blob[HASH_HEX_SIZE];
    char parent[HASH_HEX_SIZE];
    char author[128];
    char timestamp[HASH_HEX_SIZE];
} commit_info_t;

int create_commit(
    const char* blob_hex,
    const char* parent_hex,
    const char* author,
    char hex[HASH_HEX_SIZE]
);
void parse_commit(char* content, commit_info_t* out);

#endif