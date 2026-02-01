#include <hashlog/exceptions.h>

__attribute__((noreturn)) void die(const char *fmt, ...) {
    va_list ap;

    fprintf(stderr, "fatal: ");

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fputc('\n', stderr);
    exit(128);
}