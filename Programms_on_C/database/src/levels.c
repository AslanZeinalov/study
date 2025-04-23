#include "../header_files/levels.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Имя файла базы данных для LEVELS
const char* levels_db_file = "materials/levels.db";

// Функция для парсинга строки из файла в структуру Level
void* parse_level(const char* line) {
    Level* level = (Level*)malloc(sizeof(Level));
    if (level == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    if(sscanf(line, "%d,%d,%d", &level->level, &level->cell_count, &level->protected) != 3){
       free(level);
       return NULL;
    }
    return level;
}

//Функция преобразования структуры в строку
char* level_to_string(const void* record) {
    const Level* level = (Level*)record;
    char* str = (char*)malloc(50);
    if (str == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    snprintf(str, 50, "%d,%d,%d", level->level, level->cell_count, level->protected);
    return str;
}

Level* get_level_by_id(int id) {
    return (Level*)select_by_id(levels_db_file, id, sizeof(Level), parse_level);
}

bool insert_level(const Level* level) {
    return insert_record(levels_db_file, level, sizeof(Level), level_to_string);
}

bool delete_level(int id) {
    return delete_record(levels_db_file, id, sizeof(Level), parse_level, (int[]){offsetof(Level, level)});
}
