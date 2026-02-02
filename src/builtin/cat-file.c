#include <hashlog/builtin.h>

int command_cat_file(int argc, const char** argv) {
    static const char* path = NULL;
    static const char* type = NULL;
    static char help = 0; 

    hl_object_t object = {0};

    static const hl_option_t options[] = {
        OPT_STRING('p', "path", &path, "Print the <object> based on its type."),
        OPT_STRING('t', "type", &type, "Show the object type identified by <object>."),
        OPT_BOOLEAN('h', "help", &help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    if (path) {
        object = read_object(path);
        printf("%s\n", object.content);

        goto out;
    }

    if (type) {
        object = read_object(type);
        printf("%s\n", object_string_type(object.type));

        goto out;
    }

    out:
        SECURE_FREE(object.content);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_cat_file, description, "Content or other properties of one or more objects.")