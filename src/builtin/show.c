#include <hashlog/builtin.h>

int command_show(int argc, const char** argv) {
    static const char* option_commit_hash = NULL;
    static char option_help = 0;

    hl_object_t object = {0};
    hl_object_t blob_object = {0};

    static const hl_option_t options[] = {
        OPT_POSITIONAL(&option_commit_hash, "Print the <commit>"),
        OPT_BOOLEAN('h', "help", &option_help, "Show help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (option_help) {
        print_command_help(options, ARRAY_SIZE(options));
        goto out;
    }

    if (!option_commit_hash) {
        die("A commit hash is required.");
    }

    object = read_object(option_commit_hash);
    if (object.type != COMMIT) {
        die("The hash for a option_commit_hash commit is not a commit.\n\t%s", option_commit_hash);
    }
    
    commit_info_t info = {0};

    parse_commit(object.content, &info);

    blob_object = read_object(info.blob);

    printf(BOLD("Author") ":\t%s\n", info.author);
    printf(BOLD("Date") ":\t%s\n\n", info.timestamp);
    printf("%s\n", blob_object.content);

    out:
        SECURE_FREE(object.content);
        SECURE_FREE(blob_object.content);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(command_show, description, "Show the content of a message or commit.")