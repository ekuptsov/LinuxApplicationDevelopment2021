#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

typedef int (*remove_f_type)(const char* fname);

int remove(const char* fname)
{
    remove_f_type orig_remove;
    orig_remove = (remove_f_type) dlsym(RTLD_NEXT, "remove");
    
    if (strstr(fname, "PROTECT") == NULL) {
        return orig_remove(fname);
    } else {
        return 0;
    }
}