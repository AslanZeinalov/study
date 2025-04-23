#ifndef LEVELS_H
#define LEVELS_H

#include "shared.h" // Необходимо для Level
#include <stddef.h>

void* parse_level(const char* line);
char* level_to_string(const void* record);
Level* get_level_by_id(int id);
bool insert_level(const Level* level);
bool delete_level(int id);

#endif
