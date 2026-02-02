#include <stdio.h>
#include <string.h>

#include <hashlog/builtin.h>
#include <hashlog/core/config.h>

int main(int argc, const char** argv) {
    init_config();

    const char* command;

    argv++;
    argc--;

    if (!argc) {
        return 1;
    }

    command = argv[0];
    
    hl_command_struct_t* builtin = get_builtin(command);
    if (builtin) {
        builtin->function(argc, argv);
        return 0;
    }
    
    return 1;
}