#include <hashlog/builtin/help.h>

void print_command_help(const char *cmd, const hl_option_t *options, size_t options_len) {
    const char* description = dump_command("description");
    const char* usage = dump_command("usage");

    printf(BOLD("SYNOPSIS") "\n");
    printf("\t" UNDERLINE("%s") " " "%s\n", cmd, usage);
    printf("\n");
    printf(BOLD("DESCRIPTION") "\n");
    printf("\t%s\n", description);
    printf("\n");
    printf(BOLD("OPTIONS") "\n");
    for (size_t i = 0; i < options_len; i++) {
        printf("\t%-3s %-14s %s\n",
            (char[3]){'-', options[i].short_name, '\0'},
            options[i].long_name,
            options[i].description);
    }
}