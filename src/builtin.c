#include <hashlog/builtin.h>

const char* dump_command(const char* command_symbol, const char* key) {
    const char* p = __start_commandinfo;
    size_t sym_len = strlen(command_symbol);
    size_t key_len = strlen(key);

    while (p < __stop_commandinfo) {
        // formato: command.<symbol>.<key>=<value>
        if (strncmp(p, "command.", 8) == 0 &&
            strncmp(p + 8, command_symbol, sym_len) == 0 &&
            p[8 + sym_len] == '.' &&
            strncmp(p + 9 + sym_len, key, key_len) == 0 &&
            p[9 + sym_len + key_len] == '=') {

            return p + 10 + sym_len + key_len;
        }

        p += strlen(p) + 1;
    }

    return "";
}

hl_command_struct_t commands[] = {
    { "hash-object", &command_hash_object },
    { "cat-file", &command_cat_file },
    { "post", &command_post },
    { "show", &command_show },
    { "log", &command_log },
    { "help", &command_help }
};

const size_t commands_len = sizeof(commands) / sizeof(hl_command_struct_t);

hl_command_struct_t* get_builtin(const char* str) {
    for (size_t i = 0; i < commands_len; i++) {
        if (!strcmp(str, commands[i].command)) {
            return &(commands[i]);
        }
    }
    return NULL;
}