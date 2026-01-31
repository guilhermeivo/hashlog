#ifndef HASHLOG_OPTIONS_H
#define HASHLOG_OPTIONS_H

#include "hashlog/core/config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum parse_opt_type {
	OPTION_STRING,
	OPTION_INTEGER,
	OPTION_FILENAME,
    OPTION_BOOLEAN
};

typedef struct {
	enum parse_opt_type type;
	int short_name;
	const char* long_name;
	void *value;
    const char* description;
} hl_option_t;

#define OPT_STRING(s, l, v, h) {    \
    .type = OPTION_STRING,          \
    .short_name = (s),              \
    .long_name = (l),               \
    .value = (v),                   \
    .description = (h)              \
}

#define OPT_BOOLEAN(s, l, v, h) {   \
    .type = OPTION_BOOLEAN,         \
    .short_name = (s),              \
    .long_name = (l),               \
    .value = (v),                   \
    .description = (h)              \
}

#define OPTION_INTEGER(s, l, v, h) {\
    .type = OPTION_STRING,          \
    .short_name = (s),              \
    .long_name = (l),               \
    .value = (v),                   \
    .description = (h)              \
}

#define OPT_FILENAME(s, l, v, h) {  \
    .type = OPTION_FILENAME,        \
    .short_name = (s),              \
    .long_name = (l),               \
    .value = (v),                   \
    .description = (h)              \
}

int parse_options(const hl_option_t* options, size_t options_length, int argc, const char** argv);
void free_options(const hl_option_t* options, size_t options_length);

#endif