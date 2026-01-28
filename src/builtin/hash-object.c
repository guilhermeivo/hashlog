#include <hashlog/builtin.h>

#include <hashlog/core/object.h>

int command_hash_object(int argc, const char** argv) {
    char *content = "Meu conteudo!!";
    hl_object_t object = {
        .type = BLOB,
        .content_size = 15,
        .content = &content
    };
    init_object(&object);

    size_t buffer_length = object.size;
    char* buffer = (char*) malloc(buffer_length * sizeof(char));

    size_t size = build_object(&object, &buffer, buffer_length);

    unsigned int hash_size = SHA256_SIZE;
    unsigned char* hash;
    char hex[2 * hash_size + 1];

    create_hash(&buffer, size, &hash, &hash_size);
    bytes_to_hex(hash, hash_size, hex);

    write_object(hex, &buffer);

    free(buffer);
    free(hash);

    return 0;
}