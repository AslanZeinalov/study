#ifndef MODULES_H
#define MODULES_H

#include "shared.h"  // Необходимо для Module
#include <stddef.h>

void* parse_module(const char* line);
char* module_to_string(const void* record);
Module* get_module_by_id(int id);
bool insert_module(const Module* module);
bool delete_module(int id);
int get_active_module_count(const char* db_file); // Прототип агрегационной функции

#endif
