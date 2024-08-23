#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include "shared.h"

int select_status_events(int num, StatusEventRow** results, int* num_rows);
int insert_status_event(StatusEventRow* row);
int update_status_event(StatusEventRow* row);
int delete_status_event(int event_id);
int compare_status_event_rows(const void* a, const void* b);
int get_status(int id);

#endif  // STATUS_EVENTS_H
