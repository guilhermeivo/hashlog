#include <hashlog/builtin.h>

int command_update_ref(int argc, const char** argv) {
    static const char* option_category = NULL;
    static const char* option_reference = NULL;
    static char* option_new_value = NULL;
    static char option_delete = 0; 
    static char option_help = 0; 

    char* buffer = NULL;

    static const hl_option_t options[] = {
        OPT_BOOLEAN('d', "delete", &option_delete, "Delete reference."),
        OPT_POSITIONAL(&option_category, "Category (subfolder)."),
        OPT_POSITIONAL(&option_reference, "Reference name."),
        OPT_POSITIONAL(&option_new_value, "New value for the reference."),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    if (option_delete) {
        remove_ref(option_category, option_reference);
        goto out;
    }

    if (!(option_new_value && strlen(option_new_value) > 0) && !option_delete) {
        die("A new value change is necessary.");
        goto out;
    }

    size_t buffer_length = strlen(option_new_value) + 1;
    if ((buffer = (char*) malloc(buffer_length * sizeof(char))) == NULL) {
        die(EXCEEDED_MEMORY);
    }

    size_t size = build_ref(option_new_value, &buffer, buffer_length);
    load_ref(option_category, option_reference, &buffer, size);

    printf("%s/%s\n", option_category, option_reference);

    out:
        SECURE_FREE(buffer);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_update_ref, description, "Updates or creates a reference, making it point to a specific hash.")
COMMAND_INFO(command_update_ref, type, "low")