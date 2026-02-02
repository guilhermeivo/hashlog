#ifndef HASHLOG_HELP_H
#define HASHLOG_HELP_H

#include <hashlog/utils.h>
#include <hashlog/options.h>
#include <hashlog/builtin.h>

#define print_command_help(opts, len) \
    __print_command_help(__func__, opts, len)

void __print_command_help(const char* command_symbol, const hl_option_t *options, size_t options_len);

#endif