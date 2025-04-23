#ifndef MODULES_DB_H
#define MODULES_DB_H

#include "shared.h"

// Объявления extern для переменных из других файлов
extern const char* modules_db_file;
extern const char* levels_db_file;
extern const char* status_events_db_file;

// Объявления extern для функций из других файлов
extern void* parse_module(const char* line);
extern void* parse_level(const char* line);
extern void* parse_status_event(const char* line);
extern char* module_to_string(const void* record);
extern char* level_to_string(const void* record);
extern char* status_event_to_string(const void* record);
extern Module* get_module_by_id(int id);
extern bool delete_module(int id);
extern bool insert_module(const Module* module);
extern Level* get_level_by_id(int id);
extern bool delete_level(int id);
extern bool insert_level(const Level* level);
extern StatusEvent* get_status_event_by_id(int id);
extern bool insert_status_event(const StatusEvent* event);
extern bool delete_status_event(int id);
extern int get_active_module_count(const char* db_file);

// Прототипы функций для modules_db.c
void print_module(const Module* module);
void print_level(const Level* level);
void print_status_event(const StatusEvent* event);
void display_modules_table();
void display_levels_table();
void display_status_events_table();
void implement_instruction();

#endif
