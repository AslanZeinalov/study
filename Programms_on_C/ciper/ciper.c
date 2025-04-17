#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_PATH_LENGTH 256
#define MAX_INPUT_LENGTH 256

void menu() {
  printf("\nМеню программы:\n");
  printf("1. Прочитать файл\n");
  printf("2. Добавить строку в файл\n");
  printf("3. Выход из программы\n");
  printf("Введите комманду: ");
}

char *get_file_path() {
  char *file_path = malloc(MAX_FILE_PATH_LENGTH);
  if (!file_path) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  printf("Введите путь к файлу: ");
  if (fgets(file_path, MAX_FILE_PATH_LENGTH, stdin) == NULL) {
    perror("Error reading input");
    free(file_path);
    exit(EXIT_FAILURE);
  }
  file_path[strcspn(file_path, "\n")] = 0;
  return file_path;
}

void read_and_print_file(const char *file_path) {
  FILE *file = fopen(file_path, "r");
  if (!file) {
    printf("n/a\n");
    return;
  }

  int ch;

  if ((ch = fgetc(file)) == EOF) { 
    if (ferror(file)) { 
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

	printf("Введите строку для вставки: ");
	if (fgets(input_string, MAX_INPUT_LENGTH, stdin) == NULL) {
		perror("Error reading input");
		return;
	}
	input_string[strcspn(input_string, "\n")] = 0;
	FILE *file = fopen(file_path, "a");
	if(!file) {
		printf("Error opening file for appending.\n");
		return;
	}

	fprintf(file, "%s\n", input_string);
	fclose(file);
	printf("Строка успешно добавлена в файл.\n");
	read_and_print_file(file_path);
}

int main() {
  int option;
  char *file_path = NULL;

  do {
    menu();
    if (scanf("%d", &option) != 1) {
      printf("Invalid input. Pelease enter a number.\n");
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
      case 3:
        printf("Выход из программы...\n");
        break;
      default:
        printf("Неверная опция. Повторите попытку\n");
    }
  } while (option != 3);

  if(file_path) free(file_path);
  return 0;
}
