#ifndef HASHLOG_UTILS_H
#define HASHLOG_UTILS_H

#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

size_t get_places_amount(int value);
void bytes_to_hex(const unsigned char* bytes, size_t len, char* hex);
void ensure_dir(const char* dir);

#endif