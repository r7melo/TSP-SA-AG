#include "logger.h"
#include <stdio.h>
#include <stdarg.h>

static int g_log_enabled = 0;

void LogSetEnabled(int enabled) {
    g_log_enabled = enabled;
}

void PrintLog(const char *format, ...) {
    if (!g_log_enabled) return;

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
