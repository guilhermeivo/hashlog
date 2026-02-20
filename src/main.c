#include <stdio.h>
#include <string.h>

#include <hashlog/builtin.h>
#include <hashlog/core/config.h>

static int run_builtin(const char* name, int argc, const char** argv) {
    hl_command_struct_t* builtin = get_builtin(name);
    if (!builtin)
        return 1;

    return builtin->function(argc, argv);
}

int handler(int argc, const char** argv) {
    if (!argc)
        return 1;

    return run_builtin(argv[0], argc, argv);
}

int handler_default(int argc, const char** argv) {
    return run_builtin(APP_NAME, argc, argv);
}

int main(int argc, const char** argv) {
    init_config();

    if (argc > 1 && handler(argc - 1, argv + 1) == 0)
        return 0;

    return handler_default(argc, argv);
}