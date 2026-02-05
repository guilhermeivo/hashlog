#include <hashlog/refs/thread.h>

int create_thread(thread_info_t* thread_info) {
    char* buffer = NULL;

    size_t buffer_length = strlen(thread_info->head_commit) + 1;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t size = build_ref(thread_info->head_commit, &buffer, buffer_length);
    load_ref(THREAD_FOLDER, thread_info->root_commit, &buffer, size);

    SECURE_FREE(buffer);

    return 0;
}

void parse_thread(char* content, thread_info_t* out) {
    char* saveptr;
    char* line = strtok_r(content, "\n", &saveptr);

    while (line) {
        strncpy(out->head_commit, line, sizeof(out->head_commit) - 1);
        line = strtok_r(NULL, "\n", &saveptr);
    }
}