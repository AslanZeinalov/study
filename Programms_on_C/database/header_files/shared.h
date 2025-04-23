#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Структуры данных
typedef struct {
    int id;
    char name[30];
    int level;
    int cell;
    int deleted;
} Module;

typedef struct {
    int level;
    int cell_count;
    int protected;
} Level;

typedef struct {
    int id;
    int module_id;
    int new_status;
    char date[10];
    char time[8];
} StatusEvent;

// Прототипы функций
void* read_file_to_memory(const char* filename, size_t* size);
bool write_memory_to_file(const char* filename, const void* data, size_t size);
void* select_by_id(const char* db_file, int id, size_t record_size, void* (*parse_record)(const char*));
bool insert_record(const char* db_file, const void* record, size_t record_size, char* (*record_to_string)(const void*));
bool delete_record(const char* db_file, int id, size_t record_size, void* (*parse_record)(const char*), int* record_id_field);
char* record_to_string(const void* record, size_t record_size);

#endif /* SHARED_H */
