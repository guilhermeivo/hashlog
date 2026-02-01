#include <hashlog/core/object.h>

const keyvalue_t string_type[] = {
    { .key = BLOB, .value = "blob" },
    { .key = TREE, .value = "tree" },
    { .key = COMMIT, .value = "commit" }
};

char* object_string_type(const int type) {
    return string_type[type].value;
}

int object_define_type(const char* type) {
    for (size_t i = 0; i < sizeof(string_type) / sizeof(string_type[0]); i++) {
        if (!strncmp(type, string_type[i].value, 8)) {
            return string_type[i].key;
        }
    }
    return -1;
}

void init_object(hl_object_t* object) {
    object->size = 8 + get_places_amount((int) object->content_size) + object->content_size + 3;
}

size_t build_object(const hl_object_t* object, char** buffer, const size_t buffer_size) {
    return snprintf(*buffer, buffer_size, 
        "%s %ld%c%s\n", 
        object_string_type(object->type), 
        object->content_size, 
        object->type != BLOB ? '\n' : ' ',
        object->content);
}

int write_object(const char* filename, char** content) {
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
    fprintf(fptr, *content);
    fclose(fptr);
    return 0;
}

hl_object_t read_object(const char* filename) {
    hl_object_t object = {0};

    char folder[124];

    snprintf(folder, sizeof(folder), "%s/%s/%.2s/%s", ROOT_FOLDER, OBJECT_FOLDER, filename, filename + 2);

    FILE* fptr;
    if ((fptr = fopen(folder, "r")) == NULL) {
        return object;
    }
    char object_type[8];
    if (fscanf(fptr, "%7s %zu\n", object_type, &object.content_size) != 2) {
        goto finish;
    }
    object.type = object_define_type(object_type);

    object.content = (char*) malloc(sizeof(char) * (object.content_size + 1));
    if (!object.content) {
        goto finish;
    }

    size_t read = fread(object.content, 1, object.content_size, fptr);
    if (read != object.content_size) {
        SECURE_FREE(object.content);
        
        goto finish;
    }

    object.content[object.content_size] = '\0';

    init_object(&object);

    finish:
        fclose(fptr);
        return object;
}