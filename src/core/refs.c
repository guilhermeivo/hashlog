#include <hashlog/core/refs.h>

size_t build_ref(const char* content_hash, char** buffer, const size_t buffer_size) {
    int header_len = snprintf(
        *buffer,
        buffer_size,
        "%s",
        content_hash
    );

    (*buffer)[header_len] = '\0';

    return header_len + 1;
}

int write_ref(const char* subfolder, const char* filename, char* content, size_t buffer_size) {
    char folder[124];

    ensure_dir(ROOT_FOLDER);

    snprintf(folder, sizeof(folder), "%s/%s", ROOT_FOLDER, REFS_FOLDER);
    ensure_dir(folder);

    snprintf(folder, sizeof(folder), "%s/%s/%s", ROOT_FOLDER, REFS_FOLDER, subfolder);
    ensure_dir(folder);

    snprintf(folder, sizeof(folder), "%s/%s/%s/%s", ROOT_FOLDER, REFS_FOLDER, subfolder, filename);

    FILE* fptr;
    if ((fptr = fopen(folder, "wb")) == NULL) {
        return 1;
    }
    fwrite(content, 1, buffer_size, fptr);
    fclose(fptr);
    return 0;
}

char* read_ref(const char* subfolder, const char* filename, char hash[HASH_HEX_SIZE]) {
    char folder[124];

    snprintf(folder, sizeof(folder), "%s/%s/%s/%s", ROOT_FOLDER, REFS_FOLDER, subfolder, filename);

    FILE* fptr;
    if ((fptr = fopen(folder, "rb")) == NULL) {
        return NULL;
    }
    
    size_t i = 0;
    int c;

    while ((c = fgetc(fptr)) != EOF && c != '\0' && i < HASH_HEX_SIZE - 1) {
        hash[i++] = c;
    }
    hash[i] = '\0';

    fclose(fptr);
    return hash;
}

int load_ref(const char* subfolder, const char* filename, char** buffer, size_t buffer_size) {
    return write_ref(subfolder, filename, *buffer, buffer_size);
}

int remove_ref(const char* subfolder, const char* filename) {
    char folder[124];

    snprintf(folder, sizeof(folder), "%s/%s/%s/%s", ROOT_FOLDER, REFS_FOLDER, subfolder, filename);

    return remove(folder);
}