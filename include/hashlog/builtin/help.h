#ifndef HASHLOG_HELP_H
#define HASHLOG_HELP_H

#include <hashlog/utils.h>
#include <hashlog/options.h>
#include <hashlog/builtin.h>

void print_command_help(const char *cmd, const hl_option_t *options, size_t options_len);

#endif