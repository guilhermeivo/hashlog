#ifndef HASHLOG_BUILTIN_H
#define HASHLOG_BUILTIN_H

#include <stdio.h>

#include <hashlog/options.h>
#include <hashlog/utils.h>
#include <hashlog/core/object.h>
#include <hashlog/builtin/help.h>

#define COMMAND_PREFIX "command"

#define COMMAND_INFO(t, d) \
    static const char CONCAT(commandinfo_, __COUNTER__)[] \
        __attribute__((used)) \
        __attribute__((section(".commandinfo"))) \
        __attribute__((aligned(1))) \
        = COMMAND_PREFIX "." #t "=" d;

extern const char __start_commandinfo[];
extern const char __stop_commandinfo[];

int command_cat_file(int argc, const char** argv);
int command_hash_object(int argc, const char** argv);
int command_commit_tree(int argc, const char** argv);

const char* dump_command(char* command_prefix);

#endif