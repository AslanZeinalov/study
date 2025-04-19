#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Структура для записи состояния двери
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} DoorState;

// Функция для вывода записи в консоль
void print_door_state(const DoorState *state) {
    printf("%d %d %d %d %d %d %d %d\n",
           state->year, state->month, state->day,
           state->hour, state->minute, state->second,
           state->status, state->code);
}

// Функция для чтения записи из файла по индексу
int read_door_state(const char *filename, long index, DoorState *state) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return -1;
    }

    fseek(file, index * sizeof(DoorState), SEEK_SET);
    size_t read_count = fread(state, sizeof(DoorState), 1, file);

    if (read_count != 1) {
        if (feof(file)) {
            fclose(file);
            return -1;
        } else {
            fclose(file);
            perror("Ошибка чтения из файла");
            return -1;
        }
    }

    fclose(file);
    return 0;
}

// Функция для записи записи в файл по индексу
int write_door_state(const char *filename, long index, const DoorState *state) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        file = fopen(filename, "wb+");
        if (file == NULL) {
            perror("Ошибка открытия файла для записи");
            return -1;
        }
    }

    fseek(file, index * sizeof(DoorState), SEEK_SET);
    size_t write_count = fwrite(state, sizeof(DoorState), 1, file);
    fclose(file);

    if (write_count != 1) {
        perror("Ошибка записи в файл");
        return -1;
    }

    return 0;
}

// Функция для получения количества записей в файле
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    if (file_size < 0) return 0;

    if (file_size % sizeof(DoorState) != 0) {
        fprintf(stderr, "Предупреждение: Размер файла не кратен размеру структуры DoorState.\n");
    }

    return file_size / sizeof(DoorState);
}

// Функция для сравнения двух записей (для сортировки)
int compare_door_states(const DoorState *a, const DoorState *b) {
    if (a->year != b->year) return a->year - b->year;
    if (a->month != b->month) return a->month - b->month;
    if (a->day != b->day) return a->day - b->day;
    if (a->hour != b->hour) return a->hour - b->hour;
    if (a->minute != b->minute) return a->minute - b->minute;
    if (a->second != b->second) return a->second - b->second;
    if (a->status != b->status) return a->status - b->status;
    return a->code - b->code;
}

// Функция для сортировки файла с использованием алгоритма сортировки слиянием (merge sort)
int sort_file(const char *filename) {
    long file_size = get_file_size(filename);
    if (file_size <= 1) {
        // Файл уже отсортирован или пуст
        return 0;
    }

    // Выделяем временный массив для хранения данных во время слияния
    DoorState *temp_array = (DoorState*) malloc(sizeof(DoorState) * file_size);
    if (temp_array == NULL) {
        perror("Не удалось выделить память для временного массива");
        return -1;
    }

    // Реализуем сортировку слиянием на диске
    for (long width = 1; width < file_size; width = 2 * width) {
        for (long i = 0; i < file_size; i = i + 2 * width) {
            long left = i;
            long mid = i + width;
            long right = i + 2 * width;

            if (mid > file_size) mid = file_size;
            if (right > file_size) right = file_size;

            long i_left = left;
            long i_right = mid;
            long i_merged = 0;

            // Сливаем подмассивы во временный массив
            while (i_left < mid && i_right < right) {
                DoorState left_state;
                DoorState right_state;

                if (read_door_state(filename, i_left, &left_state) != 0) {
                    free(temp_array);
                    return -1;
                }

                if (read_door_state(filename, i_right, &right_state) != 0) {
                    free(temp_array);
                    return -1;
                }

                if (compare_door_states(&left_state, &right_state) <= 0) {
                    temp_array[i_merged++] = left_state;
                    i_left++;
                } else {
                    temp_array[i_merged++] = right_state;
                    i_right++;
                }
            }

            // Копируем оставшиеся элементы
            while (i_left < mid) {
                DoorState left_state;
                if (read_door_state(filename, i_left, &left_state) != 0) {
                    free(temp_array);
                    return -1;
                }
                temp_array[i_merged++] = left_state;
                i_left++;
            }
            while (i_right < right) {
                DoorState right_state;
                if (read_door_state(filename, i_right, &right_state) != 0) {
                    free(temp_array);
                    return -1;
                }
                temp_array[i_merged++] = right_state;
                i_right++;
            }

            // Записываем отсортированные данные обратно в файл
            for (long j = 0; j < i_merged; ++j) {
                if (write_door_state(filename, left + j, &temp_array[j]) != 0) {
                    free(temp_array);
                    return -1;
                }
            }
        }
    }
    free(temp_array);
    return 0;
}


// Функция для вывода содержимого файла в консоль
int print_file_contents(const char *filename) {
    long file_size = get_file_size(filename);
    if (file_size == 0) {
        printf("Файл пуст.\n");
        return 0;
    }

    DoorState state;
    for (long i = 0; i < file_size; ++i) {
        if (read_door_state(filename, i, &state) != 0) {
            return -1;
        }
        print_door_state(&state);
    }
    return 0;
}


int add_and_sort(const char *filename) {
    DoorState new_state;

    printf("Введите данные о состоянии двери (год месяц день час минута секунда статус код):\n");
    if (scanf("%d %d %d %d %d %d %d %d",
              &new_state.year, &new_state.month, &new_state.day,
              &new_state.hour, &new_state.minute, &new_state.second,
              &new_state.status, &new_state.code) != 8) {
        fprintf(stderr, "Неверный формат ввода.\n");
        return -1;
    }

    // Добавляем новое состояние в конец файла
    long file_size = get_file_size(filename);
    if (write_door_state(filename, file_size, &new_state) != 0) {
        return -1;
    }

    // Сортируем файл
    if (sort_file(filename) != 0) {
        return -1;
    }

    // Выводим отсортированное содержимое
    return print_file_contents(filename);
}


int main() {
    char filename[256];

    printf("Введите имя файла: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    int choice;
    while (1) {
        printf("\nМеню:\n");
        printf("0 - Вывести содержимое файла\n");
        printf("1 - Сортировать содержимое файла и вывести\n");
        printf("2 - Добавить запись, отсортировать и вывести\n");
        printf("Любая другая цифра - Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Неверный ввод для выбора действия.\n");
            return 1;
        }

        switch (choice) {
            case 0:
                if (print_file_contents(filename) != 0) {
                    printf("Ошибка при выводе содержимого файла.\n");
                }
                break;
            case 1:
                if (sort_file(filename) != 0) {
                    printf("Ошибка при сортировке файла.\n");
                    break;
                }

                if (print_file_contents(filename) != 0) {
                    printf("Ошибка при выводе содержимого файла.\n");
                }
                break;
            case 2:
                if (add_and_sort(filename) != 0) {
                    printf("Ошибка при добавлении записи и сортировке.\n");
                }
                break;
            default:
                printf("Выход из программы.\n");
                return 0;
        }
    }

    return 0;
}
