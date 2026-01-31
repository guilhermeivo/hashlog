#include <hashlog/options.h>

#define FILENAME "/tmp/opt_string_temp.txt"
#define MAX_SIZE 1024

int parse_options(const hl_option_t options[], size_t options_length, int argc, const char** argv) {
    int amount_options_validate = 0;
    for (int i = 0; i < argc; i++) {
        for (size_t j = 0; j < options_length; j++) {
            if (!strcmp(argv[i], (char[3]){'-', options[j].short_name, '\0'})) {
                switch (options[j].type) {
                case OPTION_STRING:
                    if (i + 1 < argc) {
                        i++;

                        *((char**) options[j].value) = (char*) malloc((sizeof(char) * strlen(argv[i])) + 1);
                        strcpy(*((char**) options[j].value), (char*) argv[i]);
                    } else {
                        FILE *fp;
                        char buffer[MAX_SIZE];
                        char command[50];

                        sprintf(command, "%s %s", TEXT_EDITOR_DEFAULT, FILENAME);
                        system(command);

                        if ((fp = fopen(FILENAME, "r")) == NULL) {
                            return 1;
                        }

                        *((char**) options[j].value) = (char*) malloc(sizeof(char) * MAX_SIZE);
                        int c = 0;
                        while (fgets(buffer, MAX_SIZE, fp) != NULL) {
                            c += snprintf(*((char**) options[j].value) + c, MAX_SIZE, "%s", buffer);
                        }

                        fclose(fp);
                        remove(FILENAME);
                    }
                    amount_options_validate += 1;
                    break;
                case OPTION_BOOLEAN:
                    *((char*) options[j].value) = 1;
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
        switch (options[j].type) {
        case OPTION_STRING:
            if (*((char**) options[j].value)) {
                free(*((char**) options[j].value));
                *((char**) options[j].value) = NULL;
            }
            break;
        
        default:
            break;
        }
    }
}