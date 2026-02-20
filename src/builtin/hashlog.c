#include <hashlog/builtin.h>

#ifndef VERSION
#define VERSION ""
#endif

int command_hashlog(int argc, const char** argv) {
    static char option_version = 0;
    static char option_help = 0;

    static const hl_option_t options[] = {
        OPT_BOOLEAN('v', "version", &option_version, "Version."),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        printf("\n");

        hl_command_struct_t* builtin = get_builtin("help");
        if (!builtin)
            return 1;

        builtin->function(argc, argv);
        goto out;
    }

    if (option_version) {
        printf("%s version %s\n", APP_NAME, VERSION);
        goto out;
    }

    out:
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_hashlog, description, 
    "Usage: hashlog [OPTION] <command> [<args>]\n\n"
    "hashlog is a tool to manage objects and messages."
)