#include <hashlog/builtin.h>

#include <stdio.h>

static const char* path = NULL;
static const char* type = NULL;

int command_cat_file(int argc, const char** argv) {
    static hl_option_t options[] = {
        OPT_STRING('p', "path", &path),
        OPT_STRING('t', "type", &type)
    };

    parse_options(options, argc - 1, argv + 1);

    free_options(options);
    
    return 0;
}