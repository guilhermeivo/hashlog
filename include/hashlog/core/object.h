#ifndef HASHLOG_OBJECT_H
#define HASHLOG_OBJECT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <hashlog/utils.h>
#include <hashlog/exceptions.h>

#include "core.h"
#include "hash.h"

#define OBJECT_FOLDER "objects"

#define BLOB 0x0
#define COMMIT 0x1

extern const keyvalue_t string_type[];

/**
 * @brief Structure that represents an object
 *
 * An object can be of two types: blob or commit.
 *
 * - BLOB: contains raw data.
 *   Example of content:
 *      "This is a test message"
 *
 * - COMMIT: it represents a snapshot of the tree at a specific point in time.
 *   Contains references to:
 *       - commit parent
 *       - message
 *
 * @note The content field stores the object's data.
 *       For blobs, it's the text of the comment.
 *       For commits, it's the commit object (parent, message, author, timestamp).
 */
typedef struct {
    int type;
    size_t content_size;
    char* content;
    size_t size;
} hl_object_t;

char* object_string_type(const int type);

int object_define_type(const char* type);

void init_object(hl_object_t* object);

size_t build_object(const hl_object_t* object, char** buffer, const size_t buffer_size);

int write_object(const char* filename, char* content, size_t buffer_size);

hl_object_t read_object(const char* filename);

/**
 * @brief Creates a hash of the content and writes the object (`write_object`).
 * 
 */
int load_object(char** buffer, size_t buffer_size, char hex[HASH_HEX_SIZE]);

#endif