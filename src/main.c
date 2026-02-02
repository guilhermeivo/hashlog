#include <stdio.h>
#include <string.h>

#include <hashlog/builtin.h>
#include <hashlog/core/config.h>

typedef struct {
	const char* command;
	int (*function)(int, const char**);
} hl_command_struct_t;

static hl_command_struct_t commands[] = {
    { "hash-object", &command_hash_object },
    { "cat-file", &command_cat_file },
    { "post", &command_post }
};

static hl_command_struct_t* get_builtin(const char* str) {
    for (size_t i = 0; i < sizeof(commands) / sizeof(hl_command_struct_t); i++) {
        if (!strcmp(str, commands[i].command)) {
            return &(commands[i]);
        }
    }
    return NULL;
}

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