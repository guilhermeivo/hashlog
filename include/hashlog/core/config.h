#ifndef HASHLOG_CONFIG_H
#define HASHLOG_CONFIG_H

#include <confuse.h>
#include <stdlib.h>
#include <string.h>

#include <hashlog/core/core.h>
#include <hashlog/utils.h>

#define TEXT_EDITOR_DEFAULT "vim"
#define AUTHOR_DEFAULT "unknown"

void init_config();
char* get_config(const char* name);

#endif