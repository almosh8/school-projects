#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} DoorState;

int read_door_state(FILE* file, DoorState* state);
int parse_date(const char* date_str, DoorState* state);
int search_door_state(const char* file_path, const char* date_str);

int main() {
    char ifile_path[2256];
    if (scanf("%s", ifile_path) != 1) {
        printf("n/a");
        return 0;
    }

    char file_path[2256] = "../";
    strcat(file_path, ifile_path);

    char date_str[333];

    if (scanf("%s", date_str) != 1) {
        printf("n/a");
        return 0;
    }

    if (search_door_state(file_path, date_str) != 0) {
        printf("n/a");
        return 0;
    }

    return 0;
}

int search_door_state(const char* file_path, const char* date_str) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        return 1;
    }

    DoorState s;
    if (parse_date(date_str, &s) != 0) {
        fclose(file);
        return 1;
    }

    DoorState state;
    while (read_door_state(file, &state) == 1) {
        if (s.year == state.year && s.month == state.month && s.day == state.day) {
            printf("%d", state.code);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
int read_door_state(FILE* file, DoorState* state) { return fread(state, sizeof(DoorState), 1, file); }

int parse_date(const char* date_str, DoorState* state) {
    if (sscanf(date_str, "%d.%d.%d", &state->day, &state->month, &state->year) != 3) {
        return 1;
    }
    state->hour = 0;
    state->minute = 0;
    state->second = 0;
    return 0;
}
