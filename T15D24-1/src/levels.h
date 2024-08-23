#ifndef LEVELS_H
#define LEVELS_H

#include "shared.h"

int select_levels(int num, LevelRow** results, int* num_rows);
int insert_level(LevelRow* row);
int update_level(LevelRow* row);
int delete_level(int level_number);

#endif  // LEVELS_H
