#include <hashlog/core/config.h>

cfg_opt_t opts[] = {
    CFG_STR("editor", TEXT_EDITOR_DEFAULT, CFGF_NONE),
    CFG_STR("author", AUTHOR_DEFAULT, CFGF_NONE),
    CFG_END()
};

const char* get_config_dir() {
    const char *xdg = getenv("XDG_CONFIG_HOME");
    if (xdg && *xdg)
        return xdg;

    const char *home = getenv("HOME");
    if (!home)
        return NULL;

    static char fallback[4096];
    snprintf(fallback, sizeof(fallback), "%s/.config", home);
    return fallback;
}

void get_path(char* path, size_t path_length) {
    snprintf(path, path_length, "%s/%s", get_config_dir(), APP_NAME);

    ensure_dir(path);

    snprintf(path, path_length, "%s/%s/config.conf", get_config_dir(), APP_NAME);
}

void init_config() {
    cfg_t *cfg = cfg_init(opts, CFGF_NONE);

    char path[4096];
    get_path(path, sizeof(path));

    cfg_parse(cfg, path);

    FILE *fp = fopen(path, "w");
    cfg_print(cfg, fp);
    fclose(fp);

    cfg_free(cfg);
}

char* get_config(char* name) {
    cfg_t *cfg = cfg_init(opts, CFGF_NONE);

    char path[4096];
    get_path(path, sizeof(path));

    cfg_parse(cfg, path);

    cfg_opt_t* options = cfg_getopt(cfg, name);

    return options->values[0]->string;
}

void set_config(char* name, char* value) {
    cfg_t *cfg = cfg_init(opts, CFGF_NONE);

    char path[4096];
    get_path(path, sizeof(path));

    cfg_parse(cfg, path);

    cfg_setstr(cfg, name, value);
}