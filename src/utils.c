#include <hashlog/utils.h>

size_t get_places_amount(int value) {
    return floor(log10(abs(value))) + 1;
}

void bytes_to_hex(const unsigned char* bytes, size_t len, char* hex) {
    static const char lut[] = "0123456789abcdef";

    for (size_t i = 0; i < len; i++) {
        hex[i * 2] = lut[bytes[i] >> 4];
        hex[i * 2 + 1] = lut[bytes[i] & 0x0F];
    }

    hex[len * 2] = '\0';
}

void ensure_dir(const char* dir) {
    mkdir(dir, 0755);
}

__attribute__((noreturn)) void die(const char *fmt, ...) {
    va_list ap;

    fprintf(stderr, "fatal: ");

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fputc('\n', stderr);
    exit(128);
}