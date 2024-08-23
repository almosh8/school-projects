#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levels.h"
#include "modules.h"
#include "shared.h"
#include "status_events.h"

#define INSERT 0
#define UPDATE 1

int insert_or_update(int action);

int main() {
    int choice;
    int table_choice;
    int id;

    do {
        printf("Modules Database Control Menu\n");
        printf("1. SELECT\n");
        printf("2. INSERT\n");
        printf("3. UPDATE\n");
        printf("4. DELETE\n");
        printf("5. Get all active additional modules (last module status is 1)\n");
        printf("6. Set modules to be deleted\n");
        printf("7. Set protected mode for module by id\n");
        printf("8. Move module by id to specified memory level and cell\n");
        printf("9. Set protection flag of the specified memory level\n");
        printf("10. Find module by id using index\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Press Enter to try again.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        void* results = NULL;
        int num_rows = 0;

        switch (choice) {
            case 1:
                printf("Please choose a table:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                if (scanf("%d", &table_choice) != 1) {
                    printf("Invalid input. Press Enter to try again.\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }
                int num_records;
                printf("Insert the number of records or leave empty to output all of them: ");
                if (scanf("%d", &num_records) != 1 || num_records == 0) {
                    num_records = -1;  // Output all records
                }

                if (table_choice == 1) {
                    select_modules(num_records, (ModuleRow**)&results, &num_rows);
                } else if (table_choice == 2) {
                    select_levels(num_records, (LevelRow**)&results, &num_rows);
                } else if (table_choice == 3) {
                    select_status_events(num_records, (StatusEventRow**)&results, &num_rows);
                } else {
                    printf("Invalid table choice.\n");
                }

                // Print the results
                if (results) {
                    if (table_choice == 1) {
                        ModuleRow* module_rows = (ModuleRow*)results;
                        for (int i = 0; i < num_rows; i++) {
                            printf("%d %s %d %d %d\n", module_rows[i].module_id, module_rows[i].module_name,
                                   module_rows[i].memory_level, module_rows[i].cell_number,
                                   module_rows[i].deletion_flag);
                        }
                    } else if (table_choice == 2) {
                        LevelRow* level_rows = (LevelRow*)results;
                        for (int i = 0; i < num_rows; i++) {
                            printf("%d %d %d\n", level_rows[i].level_number, level_rows[i].cell_count,
                                   level_rows[i].protection_flag);
                        }
                    } else if (table_choice == 3) {
                        StatusEventRow* status_event_rows = (StatusEventRow*)results;
                        for (int i = 0; i < num_rows; i++) {
                            printf("%d %d %d %s %s\n", status_event_rows[i].event_id,
                                   status_event_rows[i].module_id, status_event_rows[i].new_status,
                                   status_event_rows[i].status_change_date,
                                   status_event_rows[i].status_change_time);
                        }
                    }
                    free(results);
                } else {
                    printf("No results found.\n");
                }
                break;
            case 2:
                insert_or_update(INSERT);
                break;
            case 3:
                insert_or_update(UPDATE);
                break;
            case 4:
                printf("Please choose a table:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                if (scanf("%d", &table_choice) != 1) {
                    printf("Invalid input. Press Enter to try again.\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }

                printf("Enter primary key of deleted item\n");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input. Press Enter to try again.\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }

                if (table_choice == 1) {
                    delete_module(id);
                } else if (table_choice == 2) {
                    delete_level(id);
                } else if (table_choice == 3) {
                    delete_status_event(id);
                } else {
                    printf("Invalid table choice.\n");
                }
                break;
            case 5:
                print_active_modules();
                break;
            case 10:
                printf("Enter module id\n");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input. Press Enter to try again.\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }
                if (search_module_by_id(id)) printf("Module not found\n");
                break;
            default:
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                break;
        }
    } while (1);

    return 0;
}

int insert_or_update(int action) {
    printf("Please choose a table:\n");
    printf("1. Modules\n");
    printf("2. Levels\n");
    printf("3. Status events\n");
    int table_choice;
    if (scanf("%d", &table_choice) != 1) {
        printf("Invalid input. Press Enter to try again.\n");
        while (getchar() != '\n')
            ;
        return -1;
    }

    if (table_choice == 1) {
        if (action == 0) {  // INSERT
            ModuleRow new_module;
            printf("Enter the module ID: ");
            if (scanf("%d", &new_module.module_id) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            // fseek(stdin, 0, SEEK_END);
            // int bytesRead;
            // char c;
            // while ((bytesRead = fread(&c, sizeof(char), 1, stdin)) == 1 && c != '\n')
            //     strcat(new_module.module_name, &c);
            /*if (fgets(new_module.module_name, sizeof(new_module.module_name), stdin) != NULL) {
                new_module.module_name[strcspn(new_module.module_name, "\n")] = '\0';
            } else {
                printf("Invalid input. Please try again.\n");
                while (getchar() != '\n');
                return -1;
            }*/

            printf("Enter the new module name:\n");
            char c, s[33];
            new_module.module_name[0] = '\0';
            while (scanf("%s%c", s, &c) == 2) {
                strcat(new_module.module_name, s);
                if (c == ' ')
                    strcat(new_module.module_name, " ");
                else if (c == '\n')
                    break;
                else {
                    printf("Invalid input. Press Enter to try again.\n");
                    while (getchar() != '\n')
                        ;
                    return -1;
                }
            }
            printf("Enter the new memory level: ");
            if (scanf("%d", &new_module.memory_level) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new cell number: ");
            if (scanf("%d", &new_module.cell_number) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new deletion flag (0/1): ");
            if (scanf("%d", &new_module.deletion_flag) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            if (action == 0) {
                insert_into_table(MODULES_PATH, &new_module);
            } else {
                update_table(MODULES_PATH, &new_module);
            }
        } else {  // UPDATE
            ModuleRow new_module;
            printf("Enter the module ID: ");
            if (scanf("%d", &new_module.module_id) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new module name:\n");
            // fseek(stdin, 0, SEEK_END);
            // printf("%s", fgets(new_module.module_name, sizeof(new_module.module_name), stdin) );
            printf("Enter the new module name:\n");
            char c, s[33];
            new_module.module_name[0] = '\0';
            while (scanf("%s%c", s, &c) == 2) {
                strcat(new_module.module_name, s);
                if (c == ' ')
                    strcat(new_module.module_name, " ");
                else if (c == '\n')
                    break;
                else {
                    printf("Invalid input. Press Enter to try again.\n");
                    while (getchar() != '\n')
                        ;
                    return -1;
                }
            }
            printf("Enter the new memory level: ");
            if (scanf("%d", &new_module.memory_level) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new cell number: ");
            if (scanf("%d", &new_module.cell_number) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new deletion flag (0/1): ");
            if (scanf("%d", &new_module.deletion_flag) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            update_table(MODULES_PATH, &new_module);
        }
    } else if (table_choice == 2) {
        if (action == 0) {  // INSERT
            LevelRow new_level;
            printf("Enter the level number: ");
            if (scanf("%d", &new_level.level_number) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new cell count: ");
            if (scanf("%d", &new_level.cell_count) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new protection flag (0/1): ");
            if (scanf("%d", &new_level.protection_flag) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            insert_into_table(LEVELS_PATH, &new_level);
        } else {  // UPDATE
            LevelRow new_level;
            printf("Enter the level number: ");
            if (scanf("%d", &new_level.level_number) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new cell count: ");
            if (scanf("%d", &new_level.cell_count) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new protection flag (0/1): ");
            if (scanf("%d", &new_level.protection_flag) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            update_table(LEVELS_PATH, &new_level);
        }
    } else if (table_choice == 3) {
        if (action == 0) {  // INSERT
            StatusEventRow new_event;
            printf("Enter the event ID: ");
            if (scanf("%d", &new_event.event_id) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new module ID: ");
            if (scanf("%d", &new_event.module_id) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new status: ");
            if (scanf("%d", &new_event.new_status) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new status change date (dd.mm.yyyy): ");
            if (scanf("%s", new_event.status_change_date) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new status change time (hh:mm:ss): ");
            if (scanf("%s", new_event.status_change_time) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            insert_into_table(STATUS_EVENTS_PATH, &new_event);
        } else {  // UPDATE
            StatusEventRow new_event;
            printf("Enter the event ID: ");
            if (scanf("%d", &new_event.event_id) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new module ID: ");
            if (scanf("%d", &new_event.module_id) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new status: ");
            if (scanf("%d", &new_event.new_status) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new status change date (dd.mm.yyyy): ");
            if (scanf("%s", new_event.status_change_date) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            printf("Enter the new status change time (hh:mm:ss): ");
            if (scanf("%s", new_event.status_change_time) != 1) {
                printf("Invalid input. Press Enter to try again.\n");
                while (getchar() != '\n')
                    ;
                return -1;
            }
            update_table(STATUS_EVENTS_PATH, &new_event);
        }
    } else {
        printf("Invalid table choice.\n");
        return -1;
    }

    return 0;
}
