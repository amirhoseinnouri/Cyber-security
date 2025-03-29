#include "hook.h"

typedef int (*orig_open_f_type)(const char *, int);

int open(const char *pathname, int flags, ...) {
    orig_open_f_type orig_open;
    orig_open = (orig_open_f_type)dlsym(RTLD_NEXT, "open");

    if (strstr(pathname, "secret_file")) {
        return -1;  // Prevent access to the hidden file
    }

    return orig_open(pathname, flags);
}
