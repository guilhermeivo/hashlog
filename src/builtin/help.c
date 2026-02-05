#include <hashlog/builtin/help.h>

void __print_command_help(const char* command_symbol, const hl_option_t *options, size_t options_len) {
    const char* description = dump_command(command_symbol, "description");
    const char* type = dump_command(command_symbol, "type");

    printf("%s", description);
    if (type[0]) printf(" (%s)", type);
    printf("\n");
    for (size_t i = 0; i < options_len; i++) {
        hl_option_t option = options[i];
        if (!option.long_name && !option.short_name) continue;
        char long_name_argument[3 + strlen(option.long_name)];
        snprintf(long_name_argument, 3 + strlen(option.long_name), "--%s", option.long_name);
        printf("\t%-3s %-14s %s\n",
            option.short_name ? (char[3]){'-', option.short_name, '\0'} : "   ",
            long_name_argument,
            option.description);
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