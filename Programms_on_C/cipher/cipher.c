#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "logger/logger.h" 

#define MAX_FILE_PATH_LENGTH 256
#define MAX_INPUT_LENGTH 256

void menu() {
  printf("\nМеню программы:\n");
  printf("1. Прочитать файл\n");
  printf("2. Добавить строку в файл\n");
  printf("3. Зашифровать .с файлы и очистить .h файлы\n");
  printf("4. Выход из программы\n");
  printf("Введите комманду: ");
}

char *get_file_path() {
  char *file_path = malloc(MAX_FILE_PATH_LENGTH);
  if (!file_path) {
    log("Ошибка выделения памяти в get_file_path", ERROR);
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  printf("Введите путь к файлу: ");
  if (fgets(file_path, MAX_FILE_PATH_LENGTH, stdin) == NULL) {
    log("Ошибка чтения ввода в get_file_path", ERROR);
    perror("Error reading input");
    free(file_path);
    exit(EXIT_FAILURE);
  }
  file_path[strcspn(file_path, "\n")] = 0;
  log("Введен путь к файлу", DEBUG);
  return file_path;
}

void read_and_print_file(const char *file_path) {
    char message[256];
    snprintf(message, sizeof(message), "Чтение и вывод файла: %s", file_path);
    log(message, INFO);

  FILE *file = fopen(file_path, "r");
  if (!file) {
    snprintf(message, sizeof(message), "Не удалось открыть файл: %s", file_path);
    log(message, WARNING);
    printf("n/a\n");
    return;
  }

  int ch;

  if ((ch = fgetc(file)) == EOF) {
    if (ferror(file)) {
      snprintf(message, sizeof(message), "Ошибка чтения файла: %s", file_path);
      log(message, ERROR);
      perror("Error reading file");
      fclose(file);
      return;
    }
    printf("n/a\n");
    fclose(file);
    return;
  }
  rewind(file);

  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
  putchar('\n');
  fclose(file);
}

void input_string(const char *file_path) {
	char input_string[ MAX_INPUT_LENGTH];
    char message[256];

	printf("Введите строку для вставки: ");
	if (fgets(input_string, MAX_INPUT_LENGTH, stdin) == NULL) {
		log("Ошибка чтения ввода в input_string", ERROR);
		perror("Error reading input");
		return;
	}
	input_string[strcspn(input_string, "\n")] = 0;
	FILE *file = fopen(file_path, "a");
	if(!file) {
        snprintf(message, sizeof(message), "Ошибка открытия файла для добавления: %s", file_path);
		log(message, ERROR);
		printf("Error opening file for appending.\n");
		return;
	}

	fprintf(file, "%s\n", input_string);
	fclose(file);
    snprintf(message, sizeof(message), "Строка добавлена в файл: %s", file_path);
	log(message, INFO);
	printf("Строка успешно добавлена в файл.\n");
	read_and_print_file(file_path);
}

void caesar_cipher(char *file_path, int shift) {
    char message[256];
	snprintf(message, sizeof(message), "Попытка шифрования Цезаря для файла: %s со сдвигом: %d", file_path, shift);
	log(message, INFO);

	FILE *file = fopen(file_path, "r+");
	if(!file) {
		snprintf(message, sizeof(message), "Ошибка открытия файла для шифрования: %s", file_path);
		log(message, ERROR);
		printf("Error opening file for ciphering.\n");
		return;
	}

	int ch;
	long file_size;

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(file_size + 1);
	if (!buffer) {
		snprintf(message, sizeof(message), "Ошибка выделения памяти для файла: %s", file_path);
		log(message, ERROR);
		perror("Memory allocation failed");
		fclose(file);
		return;
	}

	fread(buffer, 1, file_size, file);
	buffer[file_size] = '\0';

	for (int i = 0; i < file_size; i++) {
		if(isalpha(buffer[i])) {
			char base = isupper (buffer[i]) ? 'A' : 'a';
			buffer[i] = (buffer[i] - base + shift) % 26 + base;
		}
	}
	rewind(file);
	fwrite(buffer, 1, file_size, file);
	fflush(file);
	fclose(file);
	free(buffer);

	snprintf(message, sizeof(message), "Файл %s успешно зашифрован с сдвигом: %d", file_path, shift);
	log(message, INFO);
	printf("Файл %s успешно зашифрованю\n", file_path);
}

void clear_h_file (char *file_path) {
    char message[256];
	snprintf(message, sizeof(message), "Попытка очистки файла: %s", file_path);
	log(message, INFO);
	FILE *file = fopen(file_path, "w");
	if(!file) {
		snprintf(message, sizeof(message), "Ошибка открытия файла для очистки: %s", file_path);
		log(message, ERROR);
		printf("Error opening file for clearing.\n");
		return;
	}
	fclose(file);
	snprintf(message, sizeof(message), "Файл %s успешно очищен", file_path);
	log(message, INFO);
	printf("Файл %s успешно очищеню\n", file_path);
}

void process_directory(char *dir_path, int shift) {
    char message[256];
    snprintf(message, sizeof(message), "Обработка директории: %s со сдвигом: %d", dir_path, shift);
    log(message, INFO);

	DIR *dir;
	struct dirent *entry;
	dir = opendir(dir_path);
	if (!dir) {
		snprintf(message, sizeof(message), "Ошибка открытия директории: %s", dir_path);
		log(message, ERROR);
		perror ("Error opening directory");
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		char full_path[MAX_FILE_PATH_LENGTH];
		snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

		if(entry->d_type == DT_REG) {
			char *ext = strrchr(entry->d_name, '.');
			if(ext != NULL) {
				if (strcmp(ext, ".c") == 0) {
					caesar_cipher(full_path, shift);
				}else if (strcmp(ext, ".h") == 0) {
					clear_h_file(full_path);
				}
			}
		}else if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
			process_directory(full_path, shift);
			}
		}
	}
	closedir(dir);
	snprintf(message, sizeof(message), "Закончена обработка директории: %s", dir_path);
    log(message, INFO);
}

int main() {
  int option;
  char *file_path = NULL;
  char *log_file_name = "cipher.log";
    char message[256];

  if (log_init(log_file_name) != 0) {
      fprintf(stderr, "Не удалось инициализировать логгер. Выход.\n");
      return EXIT_FAILURE;
  }

  log("Приложение запущено", INFO);

  do {
    menu();
    if (scanf("%d", &option) != 1) {
        log("Неверный ввод для опции меню", WARNING);
      printf("Неверный ввод. Пожалуйста, введите число.\n");
      while (getchar() != '\n');
      continue;
    }
    while (getchar() != '\n');

    switch (option) {
      case 1:
	if(file_path) free(file_path);
        file_path = get_file_path();
        read_and_print_file(file_path);
        break;
      case 2:
	if(!file_path) {
		printf("Сначала выберите файл в пункте 1.\n");
	}else {
      		input_string(file_path);
	}
        break;
	case 3: {
		char dir_path[MAX_FILE_PATH_LENGTH];
		int shift;
		printf("Введите путь к директории: ");
		if(fgets(dir_path, sizeof(dir_path), stdin) == NULL) {
			log("Ошибка чтения пути к директории", ERROR);
			perror("Error reading directory path");
			break;
		}
		dir_path[strcspn(dir_path, "\n")] = 0;

		printf("Введите сдвиг для шифра Цезаря: ");
		if(scanf("%d", &shift) != 1) {
			log("Введено неверное значение сдвига", WARNING);
			printf("Invalid shift value.\n");
			while (getchar() != '\n');
			break;
		}
		while (getchar() != '\n');

		process_directory(dir_path, shift);
		break;
		}
      case 4:
        printf("Выход из программы...\n");
        break;
      default:
        printf("Неверная опция. Повторите попытку\n");
    }
  } while (option != 4);

  if(file_path) free(file_path);
  log("Приложение завершено", INFO);
  log_close();
  return 0;
}
