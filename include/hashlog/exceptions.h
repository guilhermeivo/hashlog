#ifndef HASHLOG_EXCEPTIONS_H
#define HASHLOG_EXCEPTIONS_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define EXCEEDED_MEMORY "Execution exceeded memory limit."

__attribute__((noreturn)) void die(const char *fmt, ...);

#endif