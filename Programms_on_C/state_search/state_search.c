#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

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
            return -1;
        } else {
            perror("Ошибка чтения из файла");
            return -1;
        }
    }

    fclose(file);
    return 0;
}

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

int search_by_date(const char *filename, const char *date_str) {
    long file_size = get_file_size(filename);
    if (file_size == 0) {
        printf("n/a\n");
        return 0;
    }

    int day, month, year;
    if (sscanf(date_str, "%d.%d.%d", &day, &month, &year) != 3) {
        fprintf(stderr, "Неверный формат даты. Используйте ДД.ММ.ГГГГ.\n");
        printf("n/a\n");
        return -1;
    }

    DoorState state;
    int found = 0;

    for (long i = 0; i < file_size; ++i) {
        if (read_door_state(filename, i, &state) != 0) {
            printf("n/a\n");
            return -1;
        }

        if (state.day == day && state.month == month && state.year == year) {
            found = 1;

            FILE *code_file = fopen("code.txt", "w");
            if (code_file == NULL) {
                perror("Ошибка открытия файла code.txt для записи");
                printf("n/a\n");
                return -1;
            }

            fprintf(code_file, "%d", state.code);
            fclose(code_file);

            printf("%d\n", state.code);
            break;
        }
    }

    if (!found) {
        printf("n/a\n");
    }

    return 0;
}

int main() {
    char filename[256];
    char date_str[11];

    printf("Введите имя файла: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    printf("Введите дату (ДД.ММ.ГГГГ): ");
    if (scanf("%10s", date_str) != 1) {
        fprintf(stderr, "Ошибка чтения даты.\n");
        return 1;
    }

    return search_by_date(filename, date_str);
}
