#include "status_events.h"

int compare_status_event_rows(const void* a, const void* b) {
    const StatusEventRow* row_a = (const StatusEventRow*)a;
    const StatusEventRow* row_b = (const StatusEventRow*)b;

    int a_year, a_month, a_day;
    int b_year, b_month, b_day;
    sscanf(row_a->status_change_date, "%2d.%2d.%4d", &a_day, &a_month, &a_year);
    sscanf(row_b->status_change_date, "%2d.%2d.%4d", &b_day, &b_month, &b_year);

    if (a_year != b_year) {
        return a_year - b_year;
    }
    if (a_month != b_month) {
        return a_month - b_month;
    }
    if (a_day != b_day) {
        return a_day - b_day;
    }

    int a_hour, a_minute, a_second;
    int b_hour, b_minute, b_second;
    sscanf(row_a->status_change_time, "%2d:%2d:%2d", &a_hour, &a_minute, &a_second);
    sscanf(row_b->status_change_time, "%2d:%2d:%2d", &b_hour, &b_minute, &b_second);

    if (a_hour != b_hour) {
        return a_hour - b_hour;
    }
    if (a_minute != b_minute) {
        return a_minute - b_minute;
    }
    if (a_second != b_second) {
        return a_second - b_second;
    }

    return 0;
}

int select_status_events(int num, StatusEventRow** results, int* num_rows) {
    return select_from_table(STATUS_EVENTS_PATH, num, (void**)results, num_rows);
}

int insert_status_event(StatusEventRow* row) { return insert_into_table(STATUS_EVENTS_PATH, row); }

int update_status_event(StatusEventRow* row) { return update_table(STATUS_EVENTS_PATH, row); }

int delete_status_event(int event_id) { return delete_from_table(STATUS_EVENTS_PATH, event_id); }

int get_status(int id) {
    int num_records = -1;

    void* results = NULL;
    int num_rows = 0;
    select_status_events(num_records, (StatusEventRow**)&results, &num_rows);

    StatusEventRow* status_event_rows = (StatusEventRow*)results;

    StatusEventRow max;
    max.new_status = 0;  // default value
    char m[11] = "03.06.1020";
    for (int i = 0; i < 11; i++) max.status_change_date[i] = m[i];
    for (int i = 0; i < num_rows; i++) {
        if (status_event_rows[i].event_id == id) {
            if (compare_status_event_rows(&status_event_rows[i], &max) >= 0) {
                max = status_event_rows[i];
            }
        }
    }
    free(results);
    return max.new_status;
}

int search_item_by_id(int id) {
    FILE* file = fopen(STATUS_EVENTS_PATH, "rb");
    if (!file) {
        return 1;
    }

    int row_size = sizeof(StatusEventRow);
    int num_rows = 0;
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    num_rows = (int)(file_size / row_size);

    int low = 0;
    int high = num_rows - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        fseek(file, mid * row_size, SEEK_SET);

        StatusEventRow row;
        if (fread(&row, 1, row_size, file) != (size_t)row_size) {
            fclose(file);
            return 1;
        }

        if (row.event_id == id) {
            printf("%d %d %d %s %s\n", row.event_id, row.module_id, row.new_status, row.status_change_date,
                   row.status_change_time);
            fclose(file);
            return 0;
        } else if (row.event_id < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fclose(file);
    return 1;
}