#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header_files/modules_db.h"
#include "../header_files/modules.h"
#include "../header_files/levels.h"
#include "../header_files/status_events.h"

// Функция для вывода информации о модуле
void print_module(const Module* module) {
    if (module == NULL) {
        printf("Module is NULL\n");
        return;
    }
    printf("ID: %d, Name: %s, Level: %d, Cell: %d, Deleted: %d\n",
           module->id, module->name, module->level, module->cell, module->deleted);
}

// Функция для вывода информации об уровне
void print_level(const Level* level) {
    if (level == NULL) {
        printf("Level is NULL\n");
        return;
    }
    printf("Level: %d, Cell Count: %d, Protected: %d\n",
           level->level, level->cell_count, level->protected);
}

// Функция для вывода информации о событии статуса
void print_status_event(const StatusEvent* event) {
    if (event == NULL) {
        printf("StatusEvent is NULL\n");
        return;
    }
    printf("ID: %d, Module ID: %d, New Status: %d, Date: %s, Time: %s\n",
           event->id, event->module_id, event->new_status, event->date, event->time);
}


void display_modules_table() {
     size_t file_size;
    void* file_content = read_file_to_memory(modules_db_file, &file_size);
    if (file_content == NULL) {
         perror("Error opening modules.db");
        printf("Ошибка чтения файла modules.db\n");
        return;
    }
    char* current_line = (char*)file_content;
    char* next_line = NULL;

    printf("\n--- Содержимое таблицы MODULES ---\n");
    while (current_line != NULL && current_line < (char*)file_content + file_size) {
        next_line = strchr(current_line, '\n');
        if (next_line != NULL) {
            *next_line = '\0';
        }
        Module* module = (Module*)parse_module(current_line);
        if(module != NULL){
            print_module(module);
            free(module);
        }
       if (next_line != NULL)
       {
           current_line = next_line + 1;
       } else {
           current_line = NULL;
       }

    }
    free(file_content);
}

// Функция для вывода содержимого таблицы LEVELS
void display_levels_table() {
     size_t file_size;
    void* file_content = read_file_to_memory(levels_db_file, &file_size);
    if (file_content == NULL) {
         perror("Error opening levels.db");
        printf("Ошибка чтения файла levels.db\n");
        return;
    }
    char* current_line = (char*)file_content;
    char* next_line = NULL;

    printf("\n--- Содержимое таблицы LEVELS ---\n");
    while (current_line != NULL && current_line < (char*)file_content + file_size) {
        next_line = strchr(current_line, '\n');
        if (next_line != NULL) {
            *next_line = '\0';
        }
        Level* level = (Level*)parse_level(current_line);
        if(level != NULL){
            print_level(level);
            free(level);
        }
       if (next_line != NULL)
       {
           current_line = next_line + 1;
       } else {
           current_line = NULL;
       }

    }
    free(file_content);
}

// Функция для вывода содержимого таблицы STATUS_EVENTS
void display_status_events_table() {
     size_t file_size;
    void* file_content = read_file_to_memory(status_events_db_file, &file_size);
    if (file_content == NULL) {
         perror("Error opening status_events.db");
        printf("Ошибка чтения файла status_events.db\n");
        return;
    }
    char* current_line = (char*)file_content;
    char* next_line = NULL;

    printf("\n--- Содержимое таблицы STATUS_EVENTS ---\n");
    while (current_line != NULL && current_line < (char*)file_content + file_size) {
        next_line = strchr(current_line, '\n');
        if (next_line != NULL) {
            *next_line = '\0';
        }
        StatusEvent* event = (StatusEvent*)parse_status_event(current_line);
        if(event != NULL){
            print_status_event(event);
            free(event);
        }
       if (next_line != NULL)
       {
           current_line = next_line + 1;
       } else {
           current_line = NULL;
       }

    }
    free(file_content);
}

// Функция для реализации инструкции из List 1
void implement_instruction() {
    printf("Выполняем инструкцию из List 1...\n");

    // 1. Выключить все включенные дополнительные модули и удалить их.
    int active_module_count = get_active_module_count(modules_db_file);

    for (int i = 1; i <= active_module_count + 10; i++) //Цикл от 1 до активного модуля + 10 на всякий случай
    {
         Module* module = get_module_by_id(i);
        if(module != NULL){
            //Сначала выключаем модули (делаем deleted = 1)
             if (module->id != 0 && module->deleted == 0) {
                module->deleted = 1;
                 if(!delete_module(module->id)){ //Удаляем записи о модулях
                    perror("Error delete module id");
                 }
             }
            free(module);
        }

    }

    // 2. Главный модуль (id 0) перевести в защищенный режим (0 -> 1 -> 20).
    Module* main_module = get_module_by_id(0);
    if (main_module == NULL) {
        printf("Главный модуль не найден.\n");
        return;
    }

    // Создаем события изменения статуса для главного модуля
    StatusEvent event1 = {0, 0, 0, "dd.mm.yyyy", "hh:mm:ss"}; // Пример даты и времени
    StatusEvent event2 = {1, 0, 1, "dd.mm.yyyy", "hh:mm:ss"};
    StatusEvent event3 = {2, 0, 20, "dd.mm.yyyy", "hh:mm:ss"};

    insert_status_event(&event1);
    insert_status_event(&event2);
    insert_status_event(&event3);

    // 3. Переместить главный модуль в первую ячейку первого уровня.
    main_module->level = 1;
    main_module->cell = 1;
     if(!delete_module(0)){ //Сначала удаляем старую запись
       perror("Error delete main module id");
    }

    if(!insert_module(main_module)){
        perror("Error insert main module id");
    }

    // Освобождаем память, выделенную для main_module (важно)
    free(main_module);

    // 4. Выставить флаг защищенности 1 для первого уровня.
    Level* level1 = get_level_by_id(1);
    if (level1 == NULL) {
        printf("Первый уровень не найден.\n");
        return;
    }
    level1->protected = 1;
     if(!delete_level(level1->level)){
        perror("Error delete level id");
    }

    if(!insert_level(level1)){
        perror("Error insert level id");
    }
    free(level1);

    printf("Инструкция выполнена.\n");
}


int main() {
    int choice;

    do {
        printf("\n--- Меню управления базой данных модулей ---\n");
        printf("1. Вывести содержимое таблицы MODULES\n");
        printf("2. Вывести содержимое таблицы LEVELS\n");
        printf("3. Вывести содержимое таблицы STATUS_EVENTS\n");
        printf("4. Добавить модуль\n");
        printf("5. Удалить модуль\n");
        printf("6. Проверить, что в первой ячейке первого уровня находится только главный модуль ИИ\n");
        printf("7. Выполнить инструкцию из List 1 (перевод в защищенный режим)\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                display_modules_table();
                break;
            case 2:
                display_levels_table();
                break;
            case 3:
                display_status_events_table();
                break;
            case 4: {
                Module new_module;
                printf("Введите ID модуля: ");
                scanf("%d", &new_module.id);
                getchar(); // Consume newline

                printf("Введите название модуля: ");
                fgets(new_module.name, sizeof(new_module.name), stdin);
                new_module.name[strcspn(new_module.name, "\n")] = 0; // Remove trailing newline

                printf("Введите уровень модуля: ");
                scanf("%d", &new_module.level);

                printf("Введите номер ячейки модуля: ");
                scanf("%d", &new_module.cell);

                new_module.deleted = 0; // Default value

                if (insert_module(&new_module)) {
                    printf("Модуль успешно добавлен.\n");
                } else {
                    printf("Ошибка при добавлении модуля.\n");
                }
                break;
            }
            case 5: {
                int id_to_delete;
                printf("Введите ID модуля для удаления: ");
                scanf("%d", &id_to_delete);

                if (delete_module(id_to_delete)) {
                    printf("Модуль успешно удален.\n");
                } else {
                    printf("Ошибка при удалении модуля.\n");
                }
                break;
            }
            case 6: {
                // Реализация проверки "главного модуля ИИ"
                // Получить module_id модуля, находящегося в первой ячейке первого уровня
                // Сравнить имя полученного модуля с "главным модулем ИИ"
                Level* level1 = get_level_by_id(1);
                if (level1 == NULL) {
                    printf("Уровень 1 не найден.\n");
                    break;
                }

                Module* first_module = NULL;
                for (int i = 1; i <= level1->cell_count; i++)
                {
                    Module* temp_module = get_module_by_id(i);

                    if(temp_module != NULL && temp_module->level == 1 && temp_module->cell == 1){
                        first_module = temp_module;
                        break;
                    }
                    if(temp_module != NULL) free(temp_module);
                }

                if (first_module != NULL && strcmp(first_module->name, "Главный модуль ИИ") == 0) {
                    printf("В первой ячейке первого уровня находится только главный модуль ИИ.\n");
                } else {
                    printf("В первой ячейке первого уровня не главный модуль ИИ или ячейка пуста.\n");
                }
                if (first_module != NULL) free(first_module);
                if (level1 != NULL) free(level1);
                break;
            }

        case 7:
            implement_instruction();
            {
                // Проверка после выполнения инструкции.
                Level* level1 = get_level_by_id(1);
                if (level1 == NULL) {
                    printf("Уровень 1 не найден.\n");
                    break;
                }

                Module* first_module = NULL;
                for (int i = 1; i <= level1->cell_count; i++)
                {
                    Module* temp_module = get_module_by_id(i);

                    if (temp_module != NULL && temp_module->level == 1 && temp_module->cell == 1) {
                        first_module = temp_module;
                        break;
                    }
                    if (temp_module != NULL) free(temp_module);
                }

                if (first_module != NULL && strcmp(first_module->name, "Главный модуль ИИ") == 0) {
                    printf("После выполнения инструкции: В первой ячейке первого уровня находится только главный модуль ИИ.\n");
                } else {
                    printf("После выполнения инструкции: В первой ячейке первого уровня не главный модуль ИИ или ячейка пуста.\n");
                }
                if (first_module != NULL) free(first_module);
                if (level1 != NULL) free(level1);
                break;
            }
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
    }
} while (choice != 0);

    return 0;
}
