#include <hashlog/core/thread.h>

int create_thread(const char* commit_hex, char hex[HASH_HEX_SIZE]) {
    hl_object_t object = {0};
    object.type = THREAD;

    char* buffer = NULL;

    object.content = strdup(commit_hex);
    object.content_size = strlen(commit_hex);

    init_object(&object);

    size_t buffer_length = object.size;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t size = build_object(&object, &buffer, buffer_length);
    load_object(&buffer, size, hex);

    SECURE_FREE(buffer);

    return 0;
}

void parse_thread(char* content, thread_info_t* out) {
    char* saveptr;
    char* line = strtok_r(content, "\n", &saveptr);

    while (line) {
        strncpy(out->commit, line, sizeof(out->commit) - 1);
        line = strtok_r(NULL, "\n", &saveptr);
    }
}