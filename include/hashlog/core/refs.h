#ifndef HASHLOG_REFS_H
#define HASHLOG_REFS_H

#include <hashlog/core/core.h>
#include <hashlog/core/hash.h>
#include <hashlog/utils.h>

#define REFS_FOLDER "refs"

size_t build_ref(const char* content_hash, char** buffer, const size_t buffer_size);

int write_ref(const char* subfolder, const char* filename, char* content, size_t buffer_size);

char* read_ref(const char* subfolder, const char* filename, char hash[HASH_HEX_SIZE]);

int load_ref(const char* subfolder, const char* filename, char** buffer, size_t buffer_size);

int remove_ref(const char* subfolder, const char* filename);

#endif