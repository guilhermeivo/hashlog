#ifndef HASHLOG_BUILTIN_H
#define HASHLOG_BUILTIN_H

#include <stdio.h>

#include <hashlog/options.h>
#include <hashlog/utils.h>
#include <hashlog/core/object.h>
#include <hashlog/core/refs.h>
#include <hashlog/builtin/help.h>
#include <hashlog/objects/blob.h>
#include <hashlog/objects/commit.h>

#define COMMAND_PREFIX "command"

#define COMMAND_INFO(f, t, d) \
    static const char CONCAT(commandinfo_, __COUNTER__)[] \
        __attribute__((used)) \
        __attribute__((section(".commandinfo"))) \
        __attribute__((aligned(1))) \
        = COMMAND_PREFIX "." #f "." #t "=" d;

extern const char __start_commandinfo[];
extern const char __stop_commandinfo[];

typedef struct {
	const char* command;
	int (*function)(int, const char**);
} hl_command_struct_t;

extern hl_command_struct_t commands[];
extern const size_t commands_len;

hl_command_struct_t* get_builtin(const char* str);

int command_cat_file(int argc, const char** argv);
int command_hash_object(int argc, const char** argv);
int command_post(int argc, const char** argv);
int command_show(int argc, const char** argv);
int command_log(int argc, const char** argv);
int command_update_ref(int argc, const char** argv);
int command_dummy(int argc, const char** argv);
int command_show_ref(int argc, const char** argv);

int command_help(int argc, const char** argv);

const char* dump_command(const char* command_symbol, const char* key);

#endif