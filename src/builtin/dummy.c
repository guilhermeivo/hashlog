#include <hashlog/builtin.h>

int command_dummy(int argc, const char** argv) {
    static char* option_string_value = NULL;
    static char** option_multiple_string_value = NULL;
    static int option_boolean_value = 0;
    static char* option_positional_value_1 = NULL;
    static char* option_positional_value_2 = NULL;
    static char option_help = 0;

    static const hl_option_t options[] = {
        OPT_STRING('s', "string", &option_string_value, "string value."),
        OPT_MULTIPLE_STRING(0, "multiple-string", &option_multiple_string_value, "multiple string value."),
        OPT_BOOLEAN('b', "boolean", &option_boolean_value, "boolean value."),
        OPT_POSITIONAL(&option_positional_value_1, "positional value 1."),
        OPT_POSITIONAL(&option_positional_value_2, "positional value 2."),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    printf("string: %s\n", option_string_value);
    if (option_multiple_string_value) {
        char** __multiple_string_value = option_multiple_string_value;
        while (*__multiple_string_value != NULL) {
            printf("multiple-string %ld: %s\n", __multiple_string_value - option_multiple_string_value + 1, *__multiple_string_value);
            __multiple_string_value++;
        }
    } else {
        printf("multiple-string: %p\n", NULL);
    }
    printf("boolean: %d\n", option_boolean_value);
    printf("positional 1: %s\n", option_positional_value_1);
    printf("positional 2: %s\n", option_positional_value_2);

    out:
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_dummy, description, "Dummy command.")