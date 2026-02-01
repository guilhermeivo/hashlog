#include <hashlog/builtin.h>

int command_hash_object(int argc, const char** argv) {
    static const char* type = NULL;
    static char* write = NULL;
    static char help = 0; 

    hl_object_t object = {0};

    unsigned int hash_size = SHA256_SIZE;
    unsigned char* hash = NULL;
    char hex[2 * hash_size + 1];

    char* buffer = NULL;

    static const hl_option_t options[] = {
        OPT_STRING('t', "type", &type, "Object type."),
        OPT_STRING('w', "write", &write, "Write the object."),
        OPT_BOOLEAN('h', "help", &help, "Show this help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (help) {
        print_command_help(argv[-1], options, ARRAY_SIZE(options));
        goto out;
    }

    if (type) {
        object.type = object_define_type(type);
    } else {
        object.type = BLOB;
    }

    if (object.type < 0) {
        die("Incorrect type for the object.");
    }

    if (write && strlen(write) > 0) {
        object.content = write;
        object.content_size = strlen(write);
    } else {
        goto out;
    }

    init_object(&object);

    size_t buffer_length = object.size;
    buffer = (char*) malloc(buffer_length * sizeof(char));

    size_t size = build_object(&object, &buffer, buffer_length);

    create_hash(&buffer, size, &hash, &hash_size);
    bytes_to_hex(hash, hash_size, hex);

    write_object(hex, &buffer);

    printf("%s\n", hex);

    out:
        SECURE_FREE(buffer);
        SECURE_FREE(hash);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(usage, "hash-object [ -t <type> ] ( -w <string> )")
COMMAND_INFO(description, "")