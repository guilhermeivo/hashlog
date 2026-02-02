#include <hashlog/builtin.h>

void command_post__blob(char* message, size_t size, char* hex) {
    create_blob(message, size, hex);
}

void command_post__commit(char* blob_hex, char* reply_to, char* author, char* hex) {
    create_commit(blob_hex, reply_to, author, hex);
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

    char blob_hex[HASH_HEX_SIZE];
    command_post__blob(message, strlen(message), blob_hex);
    char hex_commit[HASH_HEX_SIZE];
    command_post__commit(blob_hex, reply_to, author, hex_commit);

    printf("%s\n", hex_commit);

    out:
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(usage, "post [ -m <message> ]")
COMMAND_INFO(description, "")