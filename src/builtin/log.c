#include <hashlog/builtin.h>

int command_log(int argc, const char** argv) {
    static const char* commit_hash = NULL;
    static char help = 0;

    hl_object_t object = {0};
    hl_object_t blob_object = {0};

    static const hl_option_t options[] = {
        OPT_STRING('h', "commit-hash", &commit_hash, ""),
        OPT_BOOLEAN('h', "help", &help, "Show this help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (help) {
        print_command_help(argv[-1], options, ARRAY_SIZE(options));
        goto out;
    }

    if (!commit_hash) {
        die("A commit hash is required.");
    }

    FILE* out = stdout;

    if (isatty(STDOUT_FILENO)) {
        out = popen("less -R", "w");
    }

    char current[HASH_HEX_SIZE];
    strncpy(current, commit_hash, HASH_HEX_SIZE);

    while (current[0]) {
        object = read_object(current);
        if (object.type != COMMIT) {
            die("The hash for a commit is not a commit.\n\t%s", commit_hash);
        }
        
        commit_info_t info = {0};

        parse_commit(object.content, &info);

        blob_object = read_object(info.blob);

        fprintf(out, "\e[33mcommit:\t%s\e[0m\n", current);
        fprintf(out, BOLD("Author") ":\t%s\n", info.author);
        fprintf(out, BOLD("Date") ":\t%s\n\n", info.timestamp);
        fprintf(out, "   %s\n", blob_object.content);

        fprintf(out, "\n");

        if (info.parent[0] == '\0') {
            break;
        }

        SECURE_FREE(object.content);
        SECURE_FREE(blob_object.content);

        strncpy(current, info.parent, HASH_HEX_SIZE);
    }

    if (out != stdout) {
        pclose(out);
    }

    out:
        SECURE_FREE(object.content);
        SECURE_FREE(blob_object.content);
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(usage, "log [ -h <commit-hash> ]")
COMMAND_INFO(description, "")