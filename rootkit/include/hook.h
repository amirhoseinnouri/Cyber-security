#ifndef HOOK_H
#define HOOK_H

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

int open(const char *pathname, int flags, ...);

#endif
