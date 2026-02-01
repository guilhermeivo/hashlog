#include <hashlog/options.h>

#define FILENAME "/tmp/opt_string_temp.txt"
#define MAX_SIZE 1024

int parse_option_string_interactive(hl_option_t option) {
    FILE *fp;
    char buffer[MAX_SIZE];
    char command[50];

    sprintf(command, "%s %s", TEXT_EDITOR_DEFAULT, FILENAME);
    system(command);

    if ((fp = fopen(FILENAME, "r")) == NULL) {
        return 1;
    }

    if ((*((char**) option.value) = (char*) malloc(sizeof(char) * MAX_SIZE)) == NULL) {
        perror(EXCEEDED_MEMORY);
        return 1;
    }
    int c = 0;
    while (fgets(buffer, MAX_SIZE, fp) != NULL) {
        c += snprintf(*((char**) option.value) + c, MAX_SIZE, "%s", buffer);
    }

    fclose(fp);
    remove(FILENAME);

    return 0;
}

int parse_option_string_argument(hl_option_t option, char* argument) {
    if ((*((char**) option.value) = (char*) malloc(sizeof(char) * (strlen(argument) + 1))) == NULL) {
        perror(EXCEEDED_MEMORY);
        return 1;
    }
    strcpy(*((char**) option.value), argument);

    return 0;
}

int parse_options(const hl_option_t options[], size_t options_length, int argc, const char** argv) {
    int amount_options_validate = 0;
    for (int i = 0; i < argc; i++) {
        for (size_t j = 0; j < options_length; j++) {
            hl_option_t option = options[j];
            if (!strcmp(argv[i], (char[3]){'-', option.short_name, '\0'})) {
                switch (option.type) {
                case OPTION_STRING:
                    if (i + 1 < argc) {
                        i++;
                        parse_option_string_argument(option, (char*) argv[i]);
                    } else {
                        parse_option_string_interactive(option);
                    }
                    amount_options_validate += 1;
                    break;
                case OPTION_MULTIPLE_STRING:
                    if (i + 1 < argc) {
                        i++;
                        char* argument = (char*) argv[i];
                        char*** value = ((char***) option.value);
                        
                        size_t size = 0;

                        if (*value) {
                            while ((*value)[size])
                                size++;
                        }

                        *value = realloc(*value, (size + 2) * sizeof(char *));
                        (*value)[size] = strdup(argument);
                        (*value)[size + 1] = NULL;
                    } else {

                    }
                    amount_options_validate += 1;
                    break;
                case OPTION_BOOLEAN:
                    *((char*) option.value) = 1;
                    amount_options_validate += 1;
                    break;
                default:
                    break;
                }
                break;
            }
        }
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
        default:
            break;
        }
    }
}