#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef LOG
#include "logger.h"
void debug(char *message);
#endif

#define MAX_LENGTH 777777
#define MAX_PATH_LENGTH 666666

void option1(char *file_path);
void option2(char *file_path);
void option3();
void print(char *file_path);

int main() {
    char choice_str[MAX_LENGTH];
    char file_path[MAX_LENGTH];

    while (1) {
        if (fgets(choice_str, sizeof(choice_str), stdin) == NULL) {
            printf("n/a");
            continue;
        }
        if (choice_str[0] == '\n') {
            continue;
        }

        int choice = atoi(choice_str);
        switch (choice) {
            case 1:
                option1(file_path);
#ifdef LOG
                char message[MAX_LENGTH];
                strcpy(message, "File '");
                strcat(message, file_path);
                strcat(message, "' open");

                debug(message);
#endif
                break;

            case 2:
                option2(file_path);
                break;

            case 3:
                option3();
                break;

            case -1:
                return 0;

            default:
                printf("n/a");
                break;
        }

        printf("\n");
    }
}

void option1(char *file_path) {
    if (scanf("%s", file_path) != 1) {
        printf("n/a");
        return;
    }

    print(file_path);
}

void option2(char *file_path) {
    char line[MAX_LENGTH];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("n/a");
        return;
    }

    FILE *file = fopen(file_path, "a");
    if (file == NULL) {
        printf("n/a");
        return;
    }

    fprintf(file, "%s", line);
    fclose(file);

#ifdef LOG
    char message[MAX_LENGTH];
    strcpy(message, "String wrote in the '");
    strcat(message, file_path);
    strcat(message, "' file");

    debug(message);
#endif

    print(file_path);
}

void print(char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("n/a");
        file_path[0] = '\0';
        return;
    }

    char buffer[1024];
    int bytes_read;
    int flag = 0;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
        flag = 1;
    }

    if (ferror(file) || !flag) {
        printf("n/a");
    }

    fclose(file);

#ifdef LOG
    char message[MAX_LENGTH];
    strcpy(message, "File '");
    strcat(message, file_path);
    strcat(message, "' printed to console");

    debug(message);
#endif
}

void option3() {
    int shift;
    char dir_path[MAX_PATH_LENGTH];

    // used shift 2 when encrypted
    // use shift -2 to decrypt
    if (scanf("%d %s", &shift, dir_path) != 2) {
        printf("n/a");
        return;
    }

    // Encrypt .c files
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        printf("n/a");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 2 && strcmp(entry->d_name + strlen(entry->d_name) - 2, ".c") == 0) {
            char file_path[MAX_PATH_LENGTH];
            strcpy(file_path, dir_path);
            strcat(file_path, "/");
            strcat(file_path, entry->d_name);

            FILE *file = fopen(file_path, "r+");
            if (file == NULL) {
                printf("n/a");
                continue;
            }

            char buffer[1024];
            int bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                for (int i = 0; i < bytes_read; i++) {
                    if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                        buffer[i] = 'a' + (buffer[i] - 'a' + shift) % 26;
                    } else if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
                        buffer[i] = 'A' + (buffer[i] - 'A' + shift) % 26;
                    }
                }
                fseek(file, -bytes_read, SEEK_CUR);
                fwrite(buffer, 1, bytes_read, file);
            }

            fclose(file);

#ifdef LOG
            char message[MAX_LENGTH];
            strcpy(message, "File '");
            strcat(message, file_path);
            strcat(message, "' encrypted with shift ");
            char s[22];
            sprintf(s, "%d", shift);

            strcat(message, s);
            debug(message);
#endif
        }
    }

    closedir(dir);

    // Clear .h files
    dir = opendir(dir_path);
    if (dir == NULL) {
        printf("n/a");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 2 && strcmp(entry->d_name + strlen(entry->d_name) - 2, ".h") == 0) {
            char file_path[MAX_PATH_LENGTH];
            strcpy(file_path, dir_path);
            strcat(file_path, "/");
            strcat(file_path, entry->d_name);

            if (remove(file_path) != 0) {
                printf("n/a");
            }
        }
    }

    closedir(dir);
}

#ifdef LOG
void debug(char *message) {
    // printf("%s", message);
    FILE *log_file = log_init("cipher.log");
    if (log_file != NULL) {
        logcat(log_file, message, LOG_LEVEL_DEBUG);
        log_close(log_file);
    }
}
#endif