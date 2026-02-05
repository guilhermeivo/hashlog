#include <hashlog/builtin.h>

int command_dummy(int argc, const char** argv) {
    static char* string_value = NULL;
    static char** multiple_string_value = NULL;
    static int boolean_value = 0;
    static char* positional_value = NULL;
    static char help = 0;

    static const hl_option_t options[] = {
        OPT_STRING('s', "string", &string_value, "string value."),
        OPT_MULTIPLE_STRING(0, "multiple-string", &multiple_string_value, "multiple string value."),
        OPT_BOOLEAN('b', "boolean", &boolean_value, "boolean value."),
        OPT_POSITIONAL(&positional_value, "positional value."),
        OPT_BOOLEAN('h', "help", &help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    printf("string: %s\n", string_value);
    char** __multiple_string_value = multiple_string_value;
    while (*__multiple_string_value != NULL) {
        printf("multiple-string %ld: %s\n", __multiple_string_value - multiple_string_value + 1, *__multiple_string_value);
        __multiple_string_value++;
    }
    printf("boolean: %d\n", boolean_value);
    printf("positional: %s\n", positional_value);

    out:
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_dummy, description, "Dummy command.")