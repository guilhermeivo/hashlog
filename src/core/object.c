#include <hashlog/core/object.h>

const keyvalue_t string_type[] = {
    { .key = BLOB, .value = "blob" },
    { .key = TREE, .value = "tree" },
    { .key = COMMIT, .value = "commit" }
};

char* object_string_type(const int type) {
    return string_type[type].value;
}

void init_object(hl_object_t* object) {
    object->size = 4 + get_places_amount((int) object->content_size) + object->content_size + 3;
}

size_t build_object(const hl_object_t* object, char** buffer, const size_t buffer_size) {
    return snprintf(*buffer, buffer_size, "%s %ld %s\n", object_string_type(object->type), object->content_size, *(object->content));
}

int write_object(const char* filename, char** buffer) {
    char folder[124];

    ensure_dir(ROOT_FOLDER);

    snprintf(folder, sizeof(folder), "%s/%s", ROOT_FOLDER, OBJECT_FOLDER);
    ensure_dir(folder);

    snprintf(folder, sizeof(folder), "%s/%s/%.2s", ROOT_FOLDER, OBJECT_FOLDER, filename);
    ensure_dir(folder);

    snprintf(folder, sizeof(folder), "%s/%s/%.2s/%s", ROOT_FOLDER, OBJECT_FOLDER, filename, filename + 2);

    FILE* fptr;
    if ((fptr = fopen(folder, "wb")) == NULL) {
        return 1;
    }
    fprintf(fptr, *buffer);
    fclose(fptr);
    return 0;
}