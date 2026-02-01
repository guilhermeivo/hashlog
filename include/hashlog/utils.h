#ifndef HASHLOG_UTILS_H
#define HASHLOG_UTILS_H

#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#define CONCAT2(a, b) a##b
#define CONCAT(a, b) CONCAT2(a, b)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define SECURE_FREE(x) \
    if (x) { \
        free(x); \
        (x) = NULL; \
    } \

#define BOLD(v) "\033[1m" v "\033[0m"
#define UNDERLINE(v) "\033[4m" v "\033[0m"

size_t get_places_amount(int value);
void bytes_to_hex(const unsigned char* bytes, size_t len, char* hex);
void ensure_dir(const char* dir);

__attribute__((noreturn)) void die(const char *fmt, ...);

#endif