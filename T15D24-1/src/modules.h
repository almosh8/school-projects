#ifndef MODULES_H
#define MODULES_H

#include "shared.h"

int select_modules(int num, ModuleRow** results, int* num_rows);
int insert_module(ModuleRow* row);
int update_module(ModuleRow* row);
int delete_module(int module_id);
void print_active_modules();
int search_module_by_id(int module_id);

#endif  // MODULES_H
