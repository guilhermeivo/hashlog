#include <hashlog/builtin.h>

const char* dump_command(char* command_prefix) {
    const char* p = __start_commandinfo;
    size_t command_prefix_length = strlen(command_prefix);
    while (p < __stop_commandinfo) {
        if (strncmp(p + strlen(COMMAND_PREFIX) + 1, command_prefix, command_prefix_length) == 0) {
            const char* desc = p + strlen(COMMAND_PREFIX) + 1 + command_prefix_length + 1;
            return desc;
        }
        p += strlen(p) + 1;
    }
    return "";
}