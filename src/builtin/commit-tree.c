#include <hashlog/builtin.h>

int command_commit_tree(int argc, const char** argv) {
    static const char* tree = NULL;
    static const char** parent = NULL;
    static const char* message = NULL;
    static char help = 0; 

    hl_object_t tree_object = {0};
    hl_object_t parent_object = {0};

    static const hl_option_t options[] = {
        OPT_STRING('t', "tree", &tree, ""),
        OPT_MULTIPLE_STRING('p', "parent", &parent, ""),
        OPT_STRING('m', "message", &message, ""),
        OPT_BOOLEAN('h', "help", &help, "Show this help message."),
    };

    if (parse_options(options, ARRAY_SIZE(options), argc - 1, argv + 1) < 0) {
        goto out;
    }

    if (help) {
        print_command_help(argv[-1], options, ARRAY_SIZE(options));
        goto out;
    }
    
    if (!tree) {
        die("Passing to a hash tree is mandatory.");
    }

    tree_object = read_object(tree);
    if (tree_object.type != TREE) {
        die("The hash for a tree is not a tree.");
    }

    if (parent) {
    }
        
    // if (parent) {
    //     parent_object = read_object(parent);
    //     if (parent_object.type != COMMIT) {
    //         die("The hash for a parent commit is not a parent commit.");
    //     }
    // }

    out:
        if (tree_object.content) {
            free(tree_object.content);
            tree_object.content = NULL;
        }
        if (parent_object.content) {
            free(parent_object.content);
            parent_object.content = NULL;
        }
        free_options(options, ARRAY_SIZE(options));
        return 0;
}

COMMAND_INFO(usage, "commit-tree ( -t <tree> ) [ -p <parent1> ... ] [ -m <message> ]")
COMMAND_INFO(description, "Content or other properties of one or more objects.")