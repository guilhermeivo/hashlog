#include <hashlog/builtin.h>

int command_log(int argc, const char** argv) {
    static const char* option_commit_hash = NULL;
    static char option_help = 0;

    hl_object_t object = {0};
    hl_object_t blob_object = {0};

    static const hl_option_t options[] = {
        OPT_POSITIONAL(&option_commit_hash, "Print the <commit> log"),
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

    FILE* out = stdout;

    if (isatty(STDOUT_FILENO)) {
        out = popen("less -R", "w");
    }

    char current[HASH_HEX_SIZE + 1];
    strncpy(current, option_commit_hash, HASH_HEX_SIZE);
    current[HASH_HEX_SIZE] = '\0';

    while (current[0]) {
        object = read_object(current);
        if (object.type != COMMIT) {
            die("The hash for a commit is not a commit.\n\t%s", option_commit_hash);
        }
        
        commit_info_t info = {0};

        parse_commit(object.content, &info);

        blob_object = read_object(info.blob);

        fprintf(out, RED("commit:\t%s") "\n", current);
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

COMMAND_INFO(command_log, description, "Show commit logs")