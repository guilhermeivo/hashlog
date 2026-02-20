#include <hashlog/builtin/help.h>

void __print_command_help(const char* command_symbol, const hl_option_t *options, size_t options_len) {
    const char* description = dump_command(command_symbol, "description");
    const char* type = dump_command(command_symbol, "type");

    printf("%s", description);
    if (type[0]) printf(" (%s)", type);
    printf("\n\n");
    printf("Options:\n");
    for (size_t i = 0; i < options_len; i++) {
        hl_option_t option = options[i];
        if (!option.long_name && !option.short_name) continue;
        char command_name[6 + strlen(option.long_name) + 1];
        snprintf(
            command_name, 
            6 + strlen(option.long_name) + 1, 
            "%s%s--%s", 
            option.short_name ? (char[3]){'-', option.short_name, '\0'} : "", option.short_name ? ", " : "", option.long_name);
        printf("  %-18s %s\n",
            command_name,
            option.description);
    }
}

int command_help(int argc, const char** argv) {
    (void)argc;
    (void)argv;

    printf("*Commands*\n");
    for (size_t i = 0; i < commands_len; i++) {
        if (strcmp(commands[i].command, "help") != 0 && strcmp(commands[i].command, APP_NAME) != 0) {
            char func_name[10 + strlen(commands[i].command)];
            snprintf(func_name, 10 + strlen(commands[i].command), 
                "command_%s", 
                commands[i].command);
            for (size_t i = 0; i < strlen(func_name); i++) {
                if (func_name[i] == '-') func_name[i] = '_';
            }
            const char* description = dump_command(func_name, "description");
            const char* type = dump_command(func_name, "type");
            
            printf("  %-18s %s", commands[i].command, description);

            if (type[0]) printf(" (%s)", type);
            printf("\n");
        }
    }
    return 0;
}

COMMAND_INFO(command_help, description, "")