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

#define TEMP_FILE_PATH "../datasets/tmp"

int read_door_state(FILE* file, DoorState* state);
int write_door_state(FILE* file, DoorState* state);
int parse_date(const char* date_str, DoorState* state);
int clear_door_state(const char* file_path, const char* date_start, const char* date_end);
int compare_door_states(const void* a, const void* b);
void print_all(const char* file_path);
void print_door_state(DoorState* state);

int main() {
    char ifile_path[2256];
    if (scanf("%s", ifile_path) != 1) {
        printf("n/a");
        return 0;
    }

    char file_path[2256] = "../";
    strcat(file_path, ifile_path);

    char date_start[333], date_end[333];

    if (scanf("%s", date_start) != 1) {
        printf("n/a");
        return 0;
    }
    if (scanf("%s", date_end) != 1) {
        printf("n/a");
        return 0;
    }

    if (clear_door_state(file_path, date_start, date_end) != 0) {
        printf("n/a");
        return 0;
    }

    print_all(file_path);

    return 0;
}

int clear_door_state(const char* file_path, const char* date_start, const char* date_end) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        return 1;
    }

    DoorState start, end;
    if (parse_date(date_start, &start) != 0 || parse_date(date_end, &end) != 0) {
        fclose(file);
        return 1;
    }
    end.hour = 666;
    end.minute = 666;
    end.second = 666;

    FILE* temp_file = fopen(TEMP_FILE_PATH, "w+b");
    if (temp_file == NULL) {
        fclose(file);
        return 1;
    }

    DoorState state;
    while (read_door_state(file, &state) == 1) {
        if (compare_door_states(&state, &start) < 0 || compare_door_states(&state, &end) > 0) {
            if (write_door_state(temp_file, &state) != 1) {
                fclose(file);
                fclose(temp_file);
                return 1;
            }
        }
    }

    fclose(file);
    fclose(temp_file);
    if (remove(file_path) != 0 || rename(TEMP_FILE_PATH, file_path) != 0) {
        return 1;
    }
    return 0;
}

int read_door_state(FILE* file, DoorState* state) { return fread(state, sizeof(DoorState), 1, file); }

int write_door_state(FILE* file, DoorState* state) { return fwrite(state, sizeof(DoorState), 1, file); }

int parse_date(const char* date_str, DoorState* state) {
    if (sscanf(date_str, "%d.%d.%d", &state->day, &state->month, &state->year) != 3) {
        return 1;
    }
    state->hour = 0;
    state->minute = 0;
    state->second = 0;
    return 0;
}

int compare_door_states(const void* a, const void* b) {
    DoorState* state_a = (DoorState*)a;
    DoorState* state_b = (DoorState*)b;

    if (state_a->year != state_b->year) {
        return state_a->year - state_b->year;
    }
    if (state_a->month != state_b->month) {
        return state_a->month - state_b->month;
    }
    if (state_a->day != state_b->day) {
        return state_a->day - state_b->day;
    }
    if (state_a->hour != state_b->hour) {
        return state_a->hour - state_b->hour;
    }
    if (state_a->minute != state_b->minute) {
        return state_a->minute - state_b->minute;
    }
    if (state_a->second != state_b->second) {
        return state_a->second - state_b->second;
    }
    return 0;
}

void print_all(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("n/a\n");
        return;
    }

    int n = 0;
    DoorState state;
    while (read_door_state(file, &state) == 1) {
        print_door_state(&state);
        n++;
    }

    fclose(file);
}

void print_door_state(DoorState* state) {
    printf("%d %d %d %d %d %d %d %d\n", state->year, state->month, state->day, state->hour, state->minute,
           state->second, state->status, state->code);
}