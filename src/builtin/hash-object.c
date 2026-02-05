#include <hashlog/builtin.h>

int command_hash_object(int argc, const char** argv) {
    static const char* option_type = NULL;
    static char* option_write = NULL;
    static char option_help = 0; 

    hl_object_t object = {0};

    char hex[HASH_HEX_SIZE];

    char* buffer = NULL;

    static const hl_option_t options[] = {
        OPT_STRING('t', "type", &option_type, "Object type."),
        OPT_STRING('w', "write", &option_write, "Write the object."),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    if (option_type) {
        object.type = object_define_type(option_type);
    } else {
        object.type = BLOB;
    }

    if (object.type < 0) {
        die("Incorrect type for the object.");
    }

    if (option_write && strlen(option_write) > 0) {
        object.content = option_write;
        object.content_size = strlen(option_write);
    } else {
        goto out;
    }

    init_object(&object);

    size_t buffer_length = object.size;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t size = build_object(&object, &buffer, buffer_length);
    load_object(&buffer, size, hex);

    printf("%s\n", hex);

    out:
        SECURE_FREE(buffer);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_hash_object, description, "Calculate the object ID and create an object as input.")
COMMAND_INFO(command_hash_object, type, "low")