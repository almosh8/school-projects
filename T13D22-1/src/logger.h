#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR 3

FILE* log_init(char* filename);
int logcat(FILE* log_file, char* message, int level);
int log_close(FILE* log_file);

#endif  // LOGGER_H
