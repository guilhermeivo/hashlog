#ifndef HASHLOG_OBJECT_H
#define HASHLOG_OBJECT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <hashlog/utils.h>

#include "core.h"
#include "hash.h"

#define OBJECT_FOLDER "objects"

#define BLOB 0x0
#define TREE 0x1
#define COMMIT 0x2

typedef struct {
    int key;
    char* value;
} keyvalue_t;

extern const keyvalue_t string_type[];

typedef struct {
    int type;
    size_t content_size;
    char* content;
    size_t size;
} hl_object_t;

char* object_string_type(const int type);
void init_object(hl_object_t* object);
size_t build_object(const hl_object_t* object, char** buffer, const size_t buffer_size);
int write_object(const char* filename, char** buffer);
hl_object_t read_object(const char* filename);

#endif