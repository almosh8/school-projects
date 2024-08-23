#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULES_PATH "../materials/master_modules.db"
#define LEVELS_PATH "../materials/master_levels.db"
#define STATUS_EVENTS_PATH "../materials/master_status_events.db"
#define TEMP_FILE_PATH "../materials/tmp.db"

// Data structures for the tables
typedef struct {
    int module_id;
    char module_name[30];
    int memory_level;
    int cell_number;
    int deletion_flag;
} ModuleRow;

typedef struct {
    int level_number;
    int cell_count;
    int protection_flag;
} LevelRow;

typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char status_change_date[11];
    char status_change_time[9];
} StatusEventRow;

// Function prototypes for general table operations
int select_from_table(const char* table_name, int num, void** results, int* num_rows);
int insert_into_table(const char* table_name, void* row_data);
int update_table(const char* table_name, void* new_row_data);
int delete_from_table(const char* table_name, int id);
int sort_items(const char* table_name);

#endif
