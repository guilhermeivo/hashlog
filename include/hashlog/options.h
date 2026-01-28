#ifndef HASHLOG_OPTIONS_H
#define HASHLOG_OPTIONS_H

#include "hashlog/core/config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum parse_opt_type {
	OPTION_STRING,
	OPTION_INTEGER,
	OPTION_FILENAME
};

typedef struct {
	enum parse_opt_type type;
	int short_name;
	const char *long_name;
	void *value;
} hl_option_t;

#define OPT_STRING(s, l, v) {       \
    .type = OPTION_STRING,          \
    .short_name = (s),              \
    .long_name = (l),               \
    .value = (v)                    \
}

#define OPTION_INTEGER(s, l, v) {   \
    .type = OPTION_STRING           \
    .short_name = (s)               \
    .long_name = (l)                \
    .value = (v)                    \
}

#define OPT_FILENAME(s, l, v) {     \
    .type = OPTION_FILENAME         \
    .short_name = (s)               \
    .long_name = (l)                \
    .value = (v)                    \
}

int parse_options(hl_option_t* options, int argc, const char** argv);
void free_options(hl_option_t* options);

#endif