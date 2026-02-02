#include <hashlog/builtin.h>

void command_post__blob(char* hex, char* message) {
    hl_object_t object = {0};
    object.type = BLOB;

    char* buffer = NULL;

    object.content = message;
    object.content_size = strlen(message);

    init_object(&object);

    size_t buffer_length = object.size;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t size = build_object(&object, &buffer, buffer_length);
    load_object(&buffer, size, hex);

    SECURE_FREE(buffer);
}

size_t create_commit_message(char* message, size_t message_size, char* reply_to, char* author, char* blob_hex) {
    memset(message, 0, message_size);

    size_t length = 0;

    length += snprintf(message + length, message_size - length, "blob %s\n", blob_hex);

    if (reply_to) {
        length += snprintf(message + length, message_size - length, "parent %s\n", reply_to);
    }

    if (author) {
        length += snprintf(message + length, message_size - length, "author %s\n", author);
    } else {
        char* __author = get_config("author");
        length += snprintf(message + length, message_size - length, "author %s\n", __author);
    }
    
    char datetime[DATETIME_SIZE];
    get_datetime(datetime);
    length += snprintf(message + length, message_size - length, "timestamp %s\n\n", datetime);

    if (length >= message_size) {
        die("Commit message too large.");
    }

    return length;
}

void command_post__commit(char* hex, char* reply_to, char* author, char* blob_hex) {
    char* message = (char*) malloc(4096 * sizeof(char));
    size_t len = create_commit_message(message, 4096, reply_to, author, blob_hex);

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
}

int command_post(int argc, const char** argv) {
    static char* message = NULL;
    static char* reply_to = NULL;
    static char* author = NULL;
    static char help = 0;

    static const hl_option_t options[] = {
        OPT_STRING('m', "message", &message, ""),
        OPT_STRING(0, "reply-to", &reply_to, ""),
        OPT_STRING(0, "author", &author, ""),
        OPT_BOOLEAN('h', "help", &help, "Show this help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (help) {
        print_command_help(argv[-1], options, ARRAY_SIZE(options));
        goto out;
    }

    if (!message) {
        die("A message is required.");
    }

    if (reply_to) {
        hl_object_t reply_to_object = {0};
        reply_to_object = read_object(reply_to);
        if (reply_to_object.type != COMMIT) {
            die("The hash for a reply_to commit is not a commit.\n\t%s", reply_to);
        }
        SECURE_FREE(reply_to_object.content);
    }

    char hex_blob[2 * SHA256_SIZE + 1];
    command_post__blob(hex_blob, message);
    char hex_commit[2 * SHA256_SIZE + 1];
    command_post__commit(hex_commit, reply_to, author, hex_blob);

    printf("%s\n", hex_commit);

    out:
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(usage, "post [ -m <message> ]")
COMMAND_INFO(description, "")