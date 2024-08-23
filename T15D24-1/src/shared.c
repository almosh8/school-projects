#include "shared.h"

int select_from_table(const char* table_name, int num, void** results, int* num_rows) {
    if (num == 0) num = -1;

    FILE* file = fopen(table_name, "rb");
    if (!file) {
        return 1;
    }

    int row_size = sizeof(ModuleRow);  // Assuming MODULES table
    if (strcmp(table_name, LEVELS_PATH) == 0) {
        row_size = sizeof(LevelRow);
    } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
        row_size = sizeof(StatusEventRow);
    }

    *num_rows = 0;
    *results = malloc(row_size * 1024);  // Assuming a maximum of 1024 rows

    void* row = malloc(row_size);
    while (fread(row, 1, row_size, file) == (size_t)row_size && (num == -1 || num > 0)) {
        memcpy(*results + (*num_rows) * row_size, row, row_size);
        (*num_rows)++;
        if (num != -1) num--;
    }

    free(row);
    fclose(file);
    return 0;
}

int insert_into_table(const char* table_name, void* row_data) {
    FILE* file = fopen(table_name, "ab");
    if (!file) {
        return 1;
    }

    int row_size = sizeof(ModuleRow);  // Assuming MODULES table
    if (strcmp(table_name, LEVELS_PATH) == 0) {
        row_size = sizeof(LevelRow);
    } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
        row_size = sizeof(StatusEventRow);
    }

    // printf("%ld\n", fwrite(row_data, 1, row_size, file));
    if (fwrite(row_data, 1, row_size, file) != (size_t)row_size) {
        fclose(file);
        return 2;
    }

    fclose(file);
    sort_items(table_name);
    return 0;
}

int update_table(const char* table_name, void* new_row_data) {
    int item_id;
    if (strcmp(table_name, MODULES_PATH) == 0) {
        item_id = ((ModuleRow*)new_row_data)->module_id;
    } else if (strcmp(table_name, LEVELS_PATH) == 0) {
        item_id = ((LevelRow*)new_row_data)->level_number;
    } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
        item_id = ((StatusEventRow*)new_row_data)->event_id;
    } else
        return 1;

    return delete_from_table(table_name, item_id) || insert_into_table(table_name, new_row_data);
}

int delete_from_table(const char* table_name, int id) {
    FILE* file = fopen(table_name, "r+b");
    if (!file) {
        return 1;
    }

    int row_size = sizeof(ModuleRow);  // Assuming MODULES table
    if (strcmp(table_name, LEVELS_PATH) == 0) {
        row_size = sizeof(LevelRow);
    } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
        row_size = sizeof(StatusEventRow);
    }

    FILE* temp_file = fopen(TEMP_FILE_PATH, "w+b");
    if (temp_file == NULL) {
        fclose(file);
        return 1;
    }

    void* row = malloc(row_size);
    // printf("%ld\n", fread(row, 1, row_size, file));
    while (fread(row, 1, row_size, file) == (size_t)row_size) {
        int item_id;
        if (strcmp(table_name, MODULES_PATH) == 0) {
            item_id = ((ModuleRow*)row)->module_id;
        } else if (strcmp(table_name, LEVELS_PATH) == 0) {
            item_id = ((LevelRow*)row)->level_number;
        } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
            item_id = ((StatusEventRow*)row)->event_id;
        } else
            return 1;

        // printf("%d %d\n", item_id, id);
        if (item_id != id) {
            // printf("%ld\n", fwrite(row, 1, row_size, temp_file));
            if (fwrite(row, 1, row_size, temp_file) != (size_t)row_size) {
                free(row);
                fclose(file);
                return 3;
            }
        }
    }

    free(row);
    fclose(file);
    fclose(temp_file);
    if (remove(table_name) != 0 || rename(TEMP_FILE_PATH, table_name) != 0) {
        return 1;
    }
    return 0;
}

int sort_items(const char* table_name) {
    FILE* file = fopen(table_name, "r+b");
    if (file == NULL) {
        return 1;
    }

    int row_size = sizeof(ModuleRow);  // Assuming MODULES table
    if (strcmp(table_name, LEVELS_PATH) == 0) {
        row_size = sizeof(LevelRow);
    } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
        row_size = sizeof(StatusEventRow);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size == 0) {
        fclose(file);
        return 1;
    }

    long num_states = file_size / row_size;

    FILE* temp_file = fopen(TEMP_FILE_PATH, "w+b");
    if (temp_file == NULL) {
        fclose(file);
        return 1;
    }

    if (strcmp(table_name, MODULES_PATH) == 0) {
        ModuleRow d, min;
        int was[num_states], p;
        for (long i = 0; i < num_states; i++) was[i] = 0;

        for (long i = 0; i < num_states; i++) {
            rewind(file);
            min.module_id = 999999;
            for (int j = 0; j < num_states; j++) {
                if (fread(&d, 1, row_size, file) != (size_t)row_size) {
                    fclose(file);
                    fclose(temp_file);
                    return 1;
                }
                if (d.module_id <= min.module_id && !was[j]) {
                    min = d;
                    p = j;
                }
            }
            if (fwrite(&min, 1, row_size, temp_file) != (size_t)row_size) {
                fclose(file);
                fclose(temp_file);
                return 1;
            }
            was[p] = 1;
        }
    }
    if (strcmp(table_name, LEVELS_PATH) == 0) {
        LevelRow d, min;
        int was[num_states], p;
        for (long i = 0; i < num_states; i++) was[i] = 0;

        for (long i = 0; i < num_states; i++) {
            rewind(file);
            min.level_number = 999999;
            for (int j = 0; j < num_states; j++) {
                if (fread(&d, 1, row_size, file) != (size_t)row_size) {
                    fclose(file);
                    fclose(temp_file);
                    return 1;
                }
                if (d.level_number <= min.level_number && !was[j]) {
                    min = d;
                    p = j;
                }
            }
            if (fwrite(&min, 1, row_size, temp_file) != (size_t)row_size) {
                fclose(file);
                fclose(temp_file);
                return 1;
            }
            was[p] = 1;
        }
    } else if (strcmp(table_name, STATUS_EVENTS_PATH) == 0) {
        StatusEventRow d, min;
        int was[num_states], p;
        for (long i = 0; i < num_states; i++) was[i] = 0;

        for (long i = 0; i < num_states; i++) {
            rewind(file);
            min.event_id = 999999;
            for (int j = 0; j < num_states; j++) {
                if (fread(&d, 1, row_size, file) != (size_t)row_size) {
                    fclose(file);
                    fclose(temp_file);
                    return 1;
                }
                if (d.event_id <= min.event_id && !was[j]) {
                    min = d;
                    p = j;
                }
            }
            if (fwrite(&min, 1, row_size, temp_file) != (size_t)row_size) {
                fclose(file);
                fclose(temp_file);
                return 1;
            }
            was[p] = 1;
        }
    }

    fclose(file);
    fclose(temp_file);
    if (remove(table_name) != 0 || rename(TEMP_FILE_PATH, table_name) != 0) {
        return 1;
    }
    return 0;
}