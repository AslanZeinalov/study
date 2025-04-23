#include "../header_files/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Функция чтения файла в память
void* read_file_to_memory(const char* filename, size_t* size) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    void* buffer = malloc(*size);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(fp);
        return NULL;
    }

    if (fread(buffer, 1, *size, fp) != *size) {
        perror("Error reading file");
        fclose(fp);
        free(buffer);
        return NULL;
    }

    fclose(fp);
    return buffer;
}

// Функция записи данных в файл
bool write_memory_to_file(const char* filename, const void* data, size_t size) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return false;
    }

    if (fwrite(data, 1, size, fp) != size) {
        perror("Error writing file");
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

// Функция поиска записи по ID
void* select_by_id(const char* db_file, int id, size_t record_size, void* (*parse_record)(const char*)) {
     size_t file_size;
    void* file_content = read_file_to_memory(db_file, &file_size);
    if (file_content == NULL) {
        return NULL;
    }

    char* current_line = (char*)file_content;
    char* next_line = NULL;
    while (current_line != NULL && current_line < (char*)file_content + file_size) {
        next_line = strchr(current_line, '\n');
        if (next_line != NULL) {
            *next_line = '\0';
        }
        void* record = parse_record(current_line);
        if(record != NULL) {
            if (record_size == sizeof(Module)) {
                Module* module = (Module*) record;
                if (module->id == id) {
                    free(file_content);
                    return record;
                }
            } else if (record_size == sizeof(Level)) {
                Level* level = (Level*) record;
                if (level->level == id) {
                    free(file_content);
                    return record;
                }
            } else if (record_size == sizeof(StatusEvent)) {
                StatusEvent* event = (StatusEvent*) record;
                if (event->id == id) {
                    free(file_content);
                    return record;
                }
            }
            free(record); //Освобождаем память, если ID не совпал
        }
        if (next_line != NULL) {
            current_line = next_line + 1;
        } else {
            current_line = NULL;
        }
    }
    free(file_content);
    return NULL;
}

// Функция для добавления записи в файл
bool insert_record(const char* db_file, const void* record, size_t record_size, char* (*record_to_string)(const void*)) {
    FILE* fp = fopen(db_file, "a"); // Открываем файл для добавления в конец
    if (fp == NULL) {
        perror("Error opening file");
        return false;
    }

    char* record_string = record_to_string(record);
    if (record_string == NULL) {
        fclose(fp);
        return false;
    }

    fprintf(fp, "%s\n", record_string); // Записываем строку в файл и добавляем перенос строки
    free(record_string);

    fclose(fp);
    return true;
}

// Функция для удаления записи по ID
bool delete_record(const char* db_file, int id, size_t record_size, void* (*parse_record)(const char*), int* record_id_field) {
    // Считываем все содержимое файла в память
    size_t file_size;
    void* file_content = read_file_to_memory(db_file, &file_size);
    if (file_content == NULL) {
        return false;
    }

    // Создаем временный файл для записи отфильтрованных данных
    const char* temp_file = "temp.db";
    FILE* temp_fp = fopen(temp_file, "wb");
    if (temp_fp == NULL) {
        perror("Error opening temp file");
        free(file_content);
        return false;
    }

    // Разбиваем файл на строки и фильтруем по ID
    char* current_line = (char*)file_content;
    char* next_line = NULL;
    while (current_line != NULL && current_line < (char*)file_content + file_size) {
        next_line = strchr(current_line, '\n');
        if (next_line != NULL) {
            *next_line = '\0'; // Заменяем символ переноса строки на нуль-терминатор
        }

        void* record = parse_record(current_line);
        if (record != NULL) {
            int current_id = 0;

            if (record_size == sizeof(Module)) {
                Module* module = (Module*)record;
                current_id = module->id;
            } else if (record_size == sizeof(Level)) {
                Level* level = (Level*)record;
                current_id = level->level;
            } else if (record_size == sizeof(StatusEvent)) {
                StatusEvent* event = (StatusEvent*)record;
                current_id = event->id;
            }

            // Проверяем, соответствует ли ID текущей записи ID для удаления
            if (current_id != id) {
                // Если ID не совпадает, записываем строку во временный файл
                fprintf(temp_fp, "%s\n", current_line);
            }

            free(record); // Освобождаем память, выделенную для записи
        }

        // Переходим к следующей строке
        if (next_line != NULL) {
            current_line = next_line + 1;
        } else {
            current_line = NULL;
        }
    }

    // Закрываем временный файл
    fclose(temp_fp);

    // Освобождаем память, выделенную для содержимого файла
    free(file_content);

    // Заменяем исходный файл временным файлом
    remove(db_file);            // Удаляем исходный файл
    rename(temp_file, db_file); // Переименовываем временный файл в исходный

    return true;
}

// Общая функция для преобразования данных записи в строку для записи в файл
char* record_to_string(const void* record, size_t record_size) {
    char* str = NULL;

    if (record_size == sizeof(Module)) {
        const Module* module = (const Module*)record;
        str = (char*)malloc(100); // Выделяем память под строку
        if (str == NULL) {
            perror("Memory allocation failed");
            return NULL;
        }
        snprintf(str, 100, "%d,%s,%d,%d,%d", module->id, module->name, module->level, module->cell, module->deleted);
    } else if (record_size == sizeof(Level)) {
        const Level* level = (const Level*)record;
        str = (char*)malloc(50); // Выделяем память под строку
        if (str == NULL) {
            perror("Memory allocation failed");
            return NULL;
        }
        snprintf(str, 50, "%d,%d,%d", level->level, level->cell_count, level->protected);
    } else if (record_size == sizeof(StatusEvent)) {
        const StatusEvent* event = (const StatusEvent*)record;
        str = (char*)malloc(150); // Выделяем память под строку
        if (str == NULL) {
            perror("Memory allocation failed");
            return NULL;
        }
        snprintf(str, 150, "%d,%d,%d,%s,%s", event->id, event->module_id, event->new_status, event->date, event->time);
    }

    return str;
}
