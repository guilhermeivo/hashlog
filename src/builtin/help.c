#include <hashlog/builtin/help.h>

void __print_command_help(const char* command_symbol, const hl_option_t *options, size_t options_len) {
    const char* description = dump_command(command_symbol, "description");

    printf("%s\n", description);
    for (size_t i = 0; i < options_len; i++) {
        char long_name_argument[3 + strlen(options[i].long_name)];
        snprintf(long_name_argument, 3 + strlen(options[i].long_name), "--%s", options[i].long_name);
        printf("\t%-3s %-14s %s\n",
            options[i].short_name ? (char[3]){'-', options[i].short_name, '\0'} : "   ",
            long_name_argument,
            options[i].description);
    }
}

int command_help(int argc, const char** argv) {
    (void)argc;
    (void)argv;

    for (size_t i = 0; i < commands_len; i++) {
        if (strcmp(commands[i].command, "help")) {
            const char *__argv[] = { "help", "--help" };
            printf(UNDERLINE("%s")": ", commands[i].command);
            commands[i].function(2, __argv);
            printf("\n");
        }
    }
    return 0;
}

COMMAND_INFO(command_help, description, "")