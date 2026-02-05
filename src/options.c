#include <hashlog/options.h>

#define FILENAME "/tmp/opt_string_temp.txt"
#define MAX_SIZE 1024

int parse_option_string_interactive(hl_option_t option) {
    FILE *fp;
    char buffer[MAX_SIZE];
    char command[50];

    if ((fp = fopen(FILENAME, "w")) == NULL) {
        return 1;
    }
    fclose(fp);

    char* editor = get_config("editor");
    sprintf(command, "%s %s", editor, FILENAME);
    free(editor);
    system(command);

    if ((fp = fopen(FILENAME, "r")) == NULL) {
        return 1;
    }

    char* value = NULL;
    if ((value = (char*) malloc(sizeof(char) * MAX_SIZE)) == NULL) {
        perror(EXCEEDED_MEMORY);
        fclose(fp);
        return 1;
    }
    size_t c = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        if (c + len >= MAX_SIZE - 1) break;
        strcpy(value + c, buffer);
        c += len;
    }
    value[c] = '\0';

    *((char**) option.value) = value;

    fclose(fp);
    remove(FILENAME);

    return 0;
}

int parse_option_string_argument(hl_option_t option, const char* argument) {
    char **ptr = (char**) option.value;
    char* value = NULL;
    if (*ptr) {
        SECURE_FREE(*ptr);
    }
    if ((value = (char*) malloc(sizeof(char) * (strlen(argument) + 1))) == NULL) {
        perror(EXCEEDED_MEMORY);
        return 1;
    }
    strcpy(value, argument);
    *ptr = value;

    return 0;
}

int parse_option_multiple_string_argument(hl_option_t option, const char* argument) {
    char*** value_ptr = ((char***) option.value);
    size_t size = 0;

    if (*value_ptr) {
        while ((*value_ptr)[size])
            size++;
    }

    *value_ptr = realloc(*value_ptr, (size + 2) * sizeof(char *));
    if (!*value_ptr) {
        perror(EXCEEDED_MEMORY);
        return 1;
    }

    (*value_ptr)[size] = strdup(argument);
    (*value_ptr)[size + 1] = NULL;

    return 0;
}

int parse_options(const hl_option_t options[], size_t options_length, int argc, const char** argv) {
    int amount_options_validate = 0;
    int positional_only = 0;

    for (int i = 0; i < argc; i++) {
        char* arg = strdup(argv[i]);
        int matched = 0;

        if (!positional_only && strcmp(arg, "--") == 0) {
            positional_only = 1;
            goto finish_loop;
        }

        if (positional_only || arg[0] != '-') {
            for (size_t j = 0; j < options_length; j++) {
                if (options[j].type == OPTION_POSITIONAL && *((char**) options[j].value) == NULL) {
                    char **ptr = (char**) options[j].value;
                    if (!*ptr) {
                        *ptr = arg;
                        arg = NULL;
                        break;
                    }
                }
            }
            goto finish_loop;
        }

        if (arg[0] == '-') {
            for (size_t j = 0; j < options_length; j++) {
                hl_option_t option = options[j];

                const char* val = NULL;

                if (option.short_name && 
                    arg[1] && 
                    arg[0] == '-' && 
                    arg[1] == option.short_name 
                    && arg[2] == '\0') {
                        matched = 1;
                        if (option.type != OPTION_BOOLEAN && i + 1 < argc) 
                            val = argv[++i];
                    }

                size_t len = strlen(option.long_name);
                if (!matched && 
                    strncmp(arg, "--", 2) == 0 && 
                    strncmp(arg + 2, option.long_name, len) == 0 &&
                    (arg[2 + len] == '=' || arg[2 + len] == '\0')) {
                        matched = 1;
                        if (arg[2 + len] == '=') 
                            val = arg + 3 + len;
                        else if (option.type != OPTION_BOOLEAN && i + 1 < argc) 
                            val = argv[++i];
                    }

                if (matched) {
                    if (option.type == OPTION_STRING) {
                        if (val) parse_option_string_argument(option, val);
                        else parse_option_string_interactive(option);
                    } else if (option.type == OPTION_MULTIPLE_STRING) {
                        if (val) parse_option_multiple_string_argument(option, val);
                        else parse_option_string_interactive(option);
                    } else if (option.type == OPTION_BOOLEAN) {
                        *(int*)option.value = 1;
                    }
                    amount_options_validate++;
                    break;
                }
            }

            if (!matched) die("Unknown option: %s\n", arg);
        }

        finish_loop:
            SECURE_FREE(arg);
    }

    return amount_options_validate;
}

void free_options(const hl_option_t* options, size_t options_length) {
    for (size_t j = 0; j < options_length; j++) {
        hl_option_t option = options[j];
        switch (option.type) {
        case OPTION_STRING:
            SECURE_FREE(*((char**) option.value))
            break;
        case OPTION_MULTIPLE_STRING:
            char*** value = ((char***) option.value);
            if (*value) {
                size_t size = 0;
                while ((*value)[size]) {
                    SECURE_FREE((*value)[size]);
                    size++;
                }
                SECURE_FREE(*value);
            }
            break;
        default:
            break;
        }
    }
}