#include <hashlog/builtin.h>

int command_cat_file(int argc, const char** argv) {
    static const char* option_path = NULL;
    static const char* option_type = NULL;
    static char option_help = 0; 

    hl_object_t object = {0};

    static const hl_option_t options[] = {
        OPT_STRING('p', "path", &option_path, "Print the <object> based on its type."),
        OPT_STRING('t', "type", &option_type, "Show the object type identified by <object>."),
        OPT_POSITIONAL(&option_path, "Print the <object>"),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    if (option_path && option_type) {
        die("It is not possible to use the arguments together.");
    }

    if (option_path) {
        object = read_object(option_path);
        printf("%s\n", object.content);

        goto out;
    }

    if (option_type) {
        object = read_object(option_type);
        printf("%s\n", object_string_type(object.type));

        goto out;
    }

    out:
        SECURE_FREE(object.content);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_cat_file, description, "Content or other properties of one or more objects.")