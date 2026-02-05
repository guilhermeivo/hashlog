#include <hashlog/core/object.h>

const keyvalue_t string_type[] = {
    { .key = BLOB, .value = "blob" },
    { .key = COMMIT, .value = "commit" }
};

char* object_string_type(const int type) {
    return string_type[type].value;
}

int object_define_type(const char* type) {
    for (size_t i = 0; i < sizeof(string_type) / sizeof(string_type[0]); i++) {
        if (strcmp(type, string_type[i].value) == 0) {
            return string_type[i].key;
        }
    }
    return -1;
}

void init_object(hl_object_t* object) {
    object->size = snprintf(
        NULL,
        0,
        "%s %zu",
        object_string_type(object->type),
        object->content_size
    ) + 1 + object->content_size;
}

size_t build_object(const hl_object_t* object, char** buffer, const size_t buffer_size) {
    int header_len = snprintf(
        *buffer,
        buffer_size,
        "%s %zu",
        object_string_type(object->type),
        object->content_size
    );

    if (header_len < 0 || (size_t) header_len + 1 + object->content_size > buffer_size) {
        return 0;
    }

    (*buffer)[header_len] = '\0';
    memcpy(*buffer + header_len + 1, object->content, object->content_size);

    return header_len + 1 + object->content_size;
}

int write_object(const char* filename, char* content, size_t buffer_size) {
    char folder[124];

    ensure_dir(ROOT_FOLDER);

    snprintf(folder, sizeof(folder), "%s/%s", ROOT_FOLDER, OBJECT_FOLDER);
    ensure_dir(folder);

    snprintf(folder, sizeof(folder), "%s/%s/%.2s", ROOT_FOLDER, OBJECT_FOLDER, filename);
    ensure_dir(folder);

    snprintf(folder, sizeof(folder), "%s/%s/%.2s/%s", ROOT_FOLDER, OBJECT_FOLDER, filename, filename + 2);

    FILE* fptr;
    if ((fptr = fopen(folder, "wb")) == NULL) {
        return 1;
    }
    fwrite(content, 1, buffer_size, fptr);
    fclose(fptr);
    return 0;
}

hl_object_t read_object(const char* filename) {
    hl_object_t object = {0};

    char folder[124];

    snprintf(folder, sizeof(folder), "%s/%s/%.2s/%s", ROOT_FOLDER, OBJECT_FOLDER, filename, filename + 2);

    FILE* fptr;
    if ((fptr = fopen(folder, "rb")) == NULL) {
        return object;
    }
    char object_type[8];
    char header[64];
    size_t i = 0;
    int c;

    while ((c = fgetc(fptr)) != EOF && c != '\0' && i < sizeof(header) - 1) {
        header[i++] = c;
    }
    header[i] = '\0';

    sscanf(header, "%7s %zu", object_type, &object.content_size);
    object.type = object_define_type(object_type);
    if (object.type < 0) {
        goto finish;
    }

    object.content = malloc(object.content_size + 1);
    size_t read = fread(object.content, 1, object.content_size, fptr);
    if (read != object.content_size) {
        SECURE_FREE(object.content);
        goto finish;
    }
    object.content[object.content_size] = '\0';

    init_object(&object);

    finish:
        fclose(fptr);
        return object;
}

int load_object(char** buffer, size_t buffer_size, char hex[HASH_HEX_SIZE]) {
    unsigned int hash_size = HASH_HEX_SIZE;
    unsigned char* hash = NULL;

    create_hash(buffer, buffer_size, &hash, &hash_size);
    bytes_to_hex(hash, hash_size, hex);

    write_object(hex, *buffer, buffer_size);

    SECURE_FREE(hash);

    return 0;
}