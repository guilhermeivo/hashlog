#include <hashlog/objects/commit.h>

size_t create_commit_message(char* message, size_t message_size, const char* parent_hex, const char* author, const char* blob_hex) {
    memset(message, 0, message_size);

    size_t length = 0;

    length += snprintf(message + length, message_size - length, "blob %s\n", blob_hex);

    if (parent_hex) {
        length += snprintf(message + length, message_size - length, "parent %s\n", parent_hex);
    }

    if (author) {
        length += snprintf(message + length, message_size - length, "author %s\n", author);
    } else {
        char* __author = get_config("author");
        length += snprintf(message + length, message_size - length, "author %s\n", __author);
        free(__author);
    }
    
    char datetime[DATETIME_SIZE];
    get_datetime(datetime);
    length += snprintf(message + length, message_size - length, "timestamp %s\n\n", datetime);

    if (length >= message_size) {
        die("Commit message too large.");
    }

    return length;
}

int create_commit(const char* blob_hex, const char* parent_hex, const char* author, char hex[HASH_HEX_SIZE]) {
    char* message = (char*) malloc(MAX_SIZE_COMMIT * sizeof(char));
    size_t len = create_commit_message(message, MAX_SIZE_COMMIT, parent_hex, author, blob_hex);

    hl_object_t object = {0};
    object.type = COMMIT;

    char* buffer = NULL;

    object.content = message;
    object.content_size = len;

    init_object(&object);

    size_t buffer_length = object.size;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t size = build_object(&object, &buffer, buffer_length);
    load_object(&buffer, size, hex);

    SECURE_FREE(buffer);
    SECURE_FREE(message);

    return 0;
}

void parse_commit(char* content, commit_info_t* out) {
    char* saveptr;
    char* line = strtok_r(content, "\n", &saveptr);

    while (line) {
        if (strncmp(line, "blob ", 5) == 0) {
            strncpy(out->blob, line + 5, sizeof(out->blob) - 1);
        } else if (strncmp(line, "parent ", 7) == 0) {
            strncpy(out->parent, line + 7, sizeof(out->parent) - 1);
        } else if (strncmp(line, "author ", 7) == 0) {
            strncpy(out->author, line + 7, sizeof(out->author) - 1);
        } else if (strncmp(line, "timestamp ", 10) == 0) {
            strncpy(out->timestamp, line + 10, sizeof(out->timestamp) - 1);
        }
        line = strtok_r(NULL, "\n", &saveptr);
    }
}