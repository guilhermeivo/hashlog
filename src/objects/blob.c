#include <hashlog/objects/blob.h>

int create_blob(char* text, size_t size, char hex[HASH_HEX_SIZE]) {
    hl_object_t object = {0};
    object.type = BLOB;

    char* buffer = NULL;

    object.content = text;
    object.content_size = size;

    init_object(&object);

    size_t buffer_length = object.size;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t written = build_object(&object, &buffer, buffer_length);
    load_object(&buffer, written, hex);

    SECURE_FREE(buffer);

    return 0;
}