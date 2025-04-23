#include "../header_files/status_events.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Имя файла базы данных для STATUS_EVENTS
const char* status_events_db_file = "materials/status_events.db";

// Функция для парсинга строки из файла в структуру StatusEvent
void* parse_status_event(const char* line) {
    StatusEvent* event = (StatusEvent*)malloc(sizeof(StatusEvent));
    if (event == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    if(sscanf(line, "%d,%d,%d,%9[^,],%7s", &event->id, &event->module_id, &event->new_status, event->date, event->time) != 5){
        free(event);
        return NULL;
    }
    return event;
}

//Функция преобразования структуры в строку
char* status_event_to_string(const void* record) {
    StatusEvent* event = (StatusEvent*)record;
    char* str = (char*)malloc(150);
    if (str == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    snprintf(str, 150, "%d,%d,%d,%s,%s", event->id, event->module_id, event->new_status, event->date, event->time);
    return str;
}

StatusEvent* get_status_event_by_id(int id) {
   return (StatusEvent*)select_by_id(status_events_db_file, id, sizeof(StatusEvent), parse_status_event);
}

bool insert_status_event(const StatusEvent* event) {
   return insert_record(status_events_db_file, event, sizeof(StatusEvent), status_event_to_string);
}

bool delete_status_event(int id) {
    return delete_record(status_events_db_file, id, sizeof(StatusEvent), parse_status_event, (int[]){offsetof(StatusEvent, id)});
}
