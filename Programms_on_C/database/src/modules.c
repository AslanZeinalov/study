#include "../header_files/modules.h"  // Изменили shared.h на modules.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// Имя файла базы данных для MODULES
const char* modules_db_file = "materials/modules.db";

// Функция для парсинга строки из файла в структуру Module
void* parse_module(const char* line) {
    Module* module = (Module*)malloc(sizeof(Module));
    if (module == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    if (sscanf(line, "%d,%29[^,],%d,%d,%d", &module->id, module->name, &module->level, &module->cell, &module->deleted) != 5) {
        free(module);
        return NULL;
    }
    return module;
}

//Функция преобразования структуры в строку
char* module_to_string(const void* record) {
    const Module* module = (Module*)record;
    char* str = (char*)malloc(100);
    if (str == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    snprintf(str, 100, "%d,%s,%d,%d,%d", module->id, module->name, module->level, module->cell, module->deleted);
    return str;
}

Module* get_module_by_id(int id) {
   return (Module*)select_by_id(modules_db_file, id, sizeof(Module), parse_module);
}

bool insert_module(const Module* module) {
    return insert_record(modules_db_file, module, sizeof(Module), module_to_string);
}

bool delete_module(int id) {
        return delete_record(modules_db_file, id, sizeof(Module), parse_module, (int[]){offsetof(Module, id)});
}

//Агрегационные запросы
int get_active_module_count(const char* db_file) {
    size_t file_size;
    void* file_content = read_file_to_memory(db_file, &file_size);
    if (file_content == NULL) {
        return -1; // Ошибка чтения файла
    }

    int count = 0;
    char* current_line = (char*)file_content;
    char* next_line = NULL;

    while (current_line != NULL && current_line < (char*)file_content + file_size) {
        next_line = strchr(current_line, '\n');
        if (next_line != NULL) {
            *next_line = '\0'; // Заменяем символ переноса строки на нуль-терминатор
        }

        // Парсим строку как Module
        Module* module = (Module*)parse_module(current_line);
        if (module != NULL) {
            // Проверяем, активен ли модуль
            if (module->deleted == 0) {
                count++;
            }
            free(module); // Освобождаем память, выделенную для модуля
        }

        // Переходим к следующей строке
        if (next_line != NULL) {
            current_line = next_line + 1;
        } else {
            current_line = NULL;
        }
    }

    free(file_content); // Освобождаем память, выделенную для файла
    return count;
}
