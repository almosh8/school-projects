#include "modules.h"

#include "status_events.h"

int select_modules(int num, ModuleRow** results, int* num_rows) {
    return select_from_table(MODULES_PATH, num, (void**)results, num_rows);
}

int insert_module(ModuleRow* row) { return insert_into_table(MODULES_PATH, row); }

int update_module(ModuleRow* row) { return update_table(MODULES_PATH, row); }

int delete_module(int module_id) { return delete_from_table(MODULES_PATH, module_id); }

void print_active_modules() {
    void* results = NULL;
    int num_rows;
    select_modules(-1, (ModuleRow**)&results, &num_rows);
    if (results) {
        ModuleRow* module_rows = (ModuleRow*)results;

        for (int i = 0; i < num_rows; i++) {
            if (get_status(module_rows[i].module_id) == 1) {
                printf("%d %s %d %d %d\n", module_rows[i].module_id, module_rows[i].module_name,
                       module_rows[i].memory_level, module_rows[i].cell_number, module_rows[i].deletion_flag);

                // ModuleRow* row = malloc(sizeof(ModuleRow));
                //*row = module_rows[i];
                // memcpy(*results + i * sizeof(ModuleRow), &module_rows[i], sizeof(ModuleRow));
            }
        }
    }
    free(results);
}

int search_module_by_id(int module_id) {
    sort_items(MODULES_PATH);

    FILE* file = fopen(MODULES_PATH, "rb");
    if (!file) {
        return 1;
    }

    int row_size = sizeof(ModuleRow);
    int num_rows = 0;
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    num_rows = (int)(file_size / row_size);

    int low = 0;
    int high = num_rows - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        rewind(file);
        fseek(file, mid * row_size, SEEK_SET);

        ModuleRow row;
        if (fread(&row, 1, row_size, file) != (size_t)row_size) {
            fclose(file);
            return 1;
        }

        if (row.module_id == module_id) {
            printf("%d %s %d %d %d\n", row.module_id, row.module_name, row.memory_level, row.cell_number,
                   row.deletion_flag);
            fclose(file);
            return 0;
        } else if (row.module_id < module_id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fclose(file);
    return 1;
}