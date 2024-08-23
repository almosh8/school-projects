#include "logger.h"

#include <stdarg.h>
#include <time.h>

FILE* log_init(char* filename) {
    FILE* log_file = fopen(filename, "a");
    if (log_file == NULL) {
        fprintf(stderr, "Failed to open log file: %s\n", filename);
    }
    return log_file;
}

int logcat(FILE* log_file, char* message, int level) {
    if (log_file == NULL) {
        return 1;
    }

    const char* level_str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);

    fprintf(log_file, "[%s] [%s] %s\n", level_str[level], time_str, message);

    return 0;
}

int log_close(FILE* log_file) {
    if (log_file != NULL) {
        fclose(log_file);
        return 0;
    }
    return 1;
}
