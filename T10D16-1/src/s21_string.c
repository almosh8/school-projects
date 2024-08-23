#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int s21_strlen(const char *str) {
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        len++;
    }
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    for (int i = 0; str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0'; i++) {
        // Do nothing, just iterate through the strings
    }
    return str1[0] - str2[0];
}

int s21_strncmp(const char *str1, const char *str2, int n) {
    for (int i = 0; i < n && str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

char *s21_strcpy(char *to, const char *from) {
    char *temp = to;
    for (int i = 0; from[i] != '\0'; i++) {
        to[i] = from[i];
    }
    to[s21_strlen(from)] = '\0';
    return temp;
}

char *s21_strcat(char *dest, const char *src) {
    int dest_len = s21_strlen(dest);
    for (int i = 0; src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + s21_strlen(src)] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    int needle_len = s21_strlen(needle);
    for (int i = 0; haystack[i] != '\0'; i++) {
        if (s21_strncmp(haystack + i, needle, needle_len) == 0) {
            return (char *)(haystack + i);
        }
    }
    return 0;
}

char *s21_strtok(char *str, const char *delim) {
    static char *last_pos = NULL;
    if (str == NULL) {
        str = last_pos;
    }

    if (str == NULL) {
        return NULL;
    }

    char *start = str;
    while (*str != '\0' && s21_strchr(delim, *str) != NULL) {
        str++;
    }

    if (*str == '\0') {
        last_pos = NULL;
        return NULL;
    }

    start = str;

    while (*str != '\0' && s21_strchr(delim, *str) == NULL) {
        str++;
    }

    if (*str != '\0') {
        *str = '\0';
        last_pos = str + 1;
    } else {
        last_pos = NULL;
    }

    return start;
}
