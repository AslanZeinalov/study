#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include "shared.h" // Необходимо для StatusEvent
#include <stddef.h>

void* parse_status_event(const char* line);
char* status_event_to_string(const void* record);
StatusEvent* get_status_event_by_id(int id);
bool insert_status_event(const StatusEvent* event);
bool delete_status_event(int id);

#endif
