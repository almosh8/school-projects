#include "print_module.h"

#include <stdio.h>
#include <time.h>

void print_log(char (*print)(char), char* message) {
    char LOG_PREFIX[] = "LOG";

    // Get the current time
    time_t current_time = time(0);
    struct tm* local_time = localtime(&current_time);

    // Format the time in HH:MM:SS format
    char time_str[9];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", local_time);

    // Print the log message
    (*print)('[');
    (*print)(LOG_PREFIX[0]);
    (*print)(LOG_PREFIX[1]);
    (*print)(LOG_PREFIX[2]);
    (*print)(']');
    (*print)(' ');
    for (char* c = time_str; *c != '\0'; c++) {
        (*print)(*c);
    }
    (*print)(' ');
    for (char* c = message; *c != '\0'; c++) {
        (*print)(*c);
    }
}

char print_char(char ch) { return putchar(ch); }
