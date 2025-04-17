#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_PATH_LENGTH 256

void menu() {
  printf("\nМеню программы:\n");
  printf("1. Прочитать файл\n");
  printf("2. (Еще не установлено)\n");
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

  // Проверяем, пуст ли файл ИЛИ произошла ошибка при чтении
  if ((ch = fgetc(file)) == EOF) { // read the first character
    if (ferror(file)) { // Check for errors during reading
      perror("Error reading file"); // Output error message to stderr
      fclose(file); // Close the file
      return;        // Exit the function
    }
    printf("n/a\n");
    fclose(file);
    return;
  }
  rewind(file); // Reset the file position

  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
  putchar('\n');
  fclose(file);
}

int main() {
  int option;
  char *file_path;

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
        file_path = get_file_path();
        read_and_print_file(file_path);
        free(file_path);
        break;
      case 2:
        printf("Опция 2 не установлена.\n");
        break;
      case 3:
        printf("Выход из программы...\n");
        break;
      default:
        printf("Неверная опция. Повторите попытку\n");
    }
  } while (option != 3);
  return 0;
}
