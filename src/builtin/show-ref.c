#include <hashlog/builtin.h>

int command_show_ref(int argc, const char** argv) {
    static const char* option_category = NULL;
    static const char* option_reference = NULL;
    static char option_help = 0; 

    static const hl_option_t options[] = {
        OPT_POSITIONAL(&option_category, "Category (subfolder)."),
        OPT_POSITIONAL(&option_reference, "Reference name."),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    char hash[HASH_HEX_SIZE];
    read_ref(option_category, option_reference, hash);

    printf("%s\n", hash);

    out:
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_show_ref, description, "Lê e exibe o hash associado a uma referência.")
COMMAND_INFO(command_show_ref, type, "low")