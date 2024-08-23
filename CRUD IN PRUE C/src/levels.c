#include "levels.h"

int select_levels(int num, LevelRow** results, int* num_rows) {
    return select_from_table(LEVELS_PATH, num, (void**)results, num_rows);
}

int insert_level(LevelRow* row) { return insert_into_table(LEVELS_PATH, row); }

int update_level(LevelRow* row) { return update_table(LEVELS_PATH, row); }

int delete_level(int level_number) { return delete_from_table(LEVELS_PATH, level_number); }
