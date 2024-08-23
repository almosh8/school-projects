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

void print_all(const char* file_path);
void print_door_state(DoorState* state);
int compare_door_states(const void* a, const void* b);
int read_door_state(FILE* file, DoorState* state);
int write_door_state(FILE* file, DoorState* state);
int sort_door_states(const char* file_path);
int add_door_state(const char* file_path);

int main() {
    char ifile_path[2256];
    if (scanf("%s", ifile_path) != 1) {
        printf("n/a");
        return 0;
    }

    char file_path[2256] = "../";
    strcat(file_path, ifile_path);

    while (1) {
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("n/a");
            return 0;
        }

        switch (choice) {
            case 0: {
                print_all(file_path);
            } break;
            case 1:
                if (sort_door_states(file_path) != 0) {
                    printf("n/a");
                    return 0;
                }
                print_all(file_path);
                break;
            case 2:
                if (add_door_state(file_path) != 0) {
                    printf("n/a");
                    return 0;
                }
                if (sort_door_states(file_path) != 0) {
                    printf("n/a");
                    return 0;
                }
                print_all(file_path);
                break;
            default:
                printf("n/a");
                return 0;
        }
    }

    return 0;
}

void print_all(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("n/a\n");
        return;
    }

    DoorState state;
    while (read_door_state(file, &state) == 1) {
        print_door_state(&state);
    }

    fclose(file);
}

void print_door_state(DoorState* state) {
    printf("%d %d %d %d %d %d %d %d\n", state->year, state->month, state->day, state->hour, state->minute,
           state->second, state->status, state->code);
}

int read_door_state(FILE* file, DoorState* state) { return fread(state, sizeof(DoorState), 1, file); }

int write_door_state(FILE* file, DoorState* state) { return fwrite(state, sizeof(DoorState), 1, file); }

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

int sort_door_states(const char* file_path) {
    FILE* file = fopen(file_path, "r+b");
    if (file == NULL) {
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size == 0) {
        fclose(file);
        return 1;
    }

    long num_states = file_size / sizeof(DoorState);

    FILE* temp_file = fopen(TEMP_FILE_PATH, "w+b");
    if (temp_file == NULL) {
        fclose(file);
        return 1;
    }

    DoorState d, min;
    int was[num_states], p;
    for (long i = 0; i < num_states; i++) was[i] = 0;

    for (long i = 0; i < num_states; i++) {
        rewind(file);
        min.year = 1000000000;
        for (int j = 0; j < num_states; j++) {
            if (read_door_state(file, &d) != 1) {
                fclose(file);
                fclose(temp_file);
                return 1;
            }
            if (compare_door_states(&d, &min) <= 0 && !was[j]) {
                min = d;
                p = j;
            }
        }
        if (write_door_state(temp_file, &min) != 1) {
            fclose(file);
            fclose(temp_file);
            return 1;
        }
        was[p] = 1;
    }

    fclose(file);
    fclose(temp_file);
    if (remove(file_path) != 0 || rename(TEMP_FILE_PATH, file_path) != 0) {
        return 1;
    }
    return 0;
}

int add_door_state(const char* file_path) {
    FILE* file = fopen(file_path, "a+b");
    if (file == NULL) {
        printf("n/a\n");
        return 1;
    }

    DoorState new_state;
    if (scanf("%d %d %d %d %d %d %d %d", &new_state.year, &new_state.month, &new_state.day, &new_state.hour,
              &new_state.minute, &new_state.second, &new_state.status, &new_state.code) != 8) {
        printf("n/a\n");
        fclose(file);
        return 1;
    }

    if (write_door_state(file, &new_state) != 1) {
        printf("n/a\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}