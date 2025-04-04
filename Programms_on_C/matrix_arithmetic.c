#include <stdio.h>
#include <stdlib.h>

void read_matrix(int rows, int cols, int ***matrix) {
  *matrix = (int **)malloc(rows * sizeof(int *));
  if (*matrix == NULL) {
    printf("n/a\n");
    exit(0);
  }
  for (int i = 0; i < rows; i++) {
    (*matrix)[i] = (int *)malloc(cols * sizeof(int));
    if ((*matrix)[i] == NULL) {
      printf("n/a\n");
      for (int j = 0; j < i; j++) {
        free((*matrix)[j]);
      }
      free(*matrix);
      exit(0);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (scanf("%d", &(*matrix)[i][j]) != 1) {
        printf("n/a\n");
        exit(0);
      }
    }
  }
}

void print_matrix(int rows, int cols, int **matrix) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d", matrix[i][j]);
      if (j < cols - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void matrix_sum(int rows, int cols, int **matrix1, int **matrix2,
                int ***result) {
  *result = (int **)malloc(rows * sizeof(int *));
  if (*result == NULL) {
    printf("n/a\n");
    exit(0);
  }
  for (int i = 0; i < rows; i++) {
    (*result)[i] = (int *)malloc(cols * sizeof(int));
    if ((*result)[i] == NULL) {
      printf("n/a\n");
      for (int j = 0; j < i; j++) {
        free((*result)[j]);
      }
      free(*result);
      exit(0);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      (*result)[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
}

void matrix_multiply(int rows1, int cols1, int rows2, int cols2, int **matrix1,
                     int **matrix2, int ***result) {
  *result = (int **)malloc(rows1 * sizeof(int *));
  if (*result == NULL) {
    printf("n/a\n");
    exit(0);
  }
  for (int i = 0; i < rows1; i++) {
    (*result)[i] = (int *)malloc(cols2 * sizeof(int));
    if ((*result)[i] == NULL) {
      printf("n/a\n");
      for (int j = 0; j < i; j++) {
        free((*result)[j]);
      }
      free(*result);
      exit(0);
    }
  }

  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols2; j++) {
      (*result)[i][j] = 0;
      for (int k = 0; k < cols1; k++) {
        (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
}

void matrix_transpose(int rows, int cols, int **matrix, int ***result) {
  *result = (int **)malloc(cols * sizeof(int *));
  if (*result == NULL) {
    printf("n/a\n");
    exit(0);
  }
  for (int i = 0; i < cols; i++) {
    (*result)[i] = (int *)malloc(rows * sizeof(int));
    if ((*result)[i] == NULL) {
      printf("n/a\n");
      for (int j = 0; j < i; j++) {
        free((*result)[j]);
      }
      free(*result);
      exit(0);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      (*result)[j][i] = matrix[i][j];
    }
  }
}

int main() {
  int operation_code;
  int rows1, cols1, rows2, cols2;
  int **matrix1 = NULL, **matrix2 = NULL, **result_matrix = NULL;

  if (scanf("%d", &operation_code) != 1) {
    printf("n/a\n");
    return 0;
  }

  if (scanf("%d %d", &rows1, &cols1) != 2) {
    printf("n/a\n");
    return 0;
  }
  read_matrix(rows1, cols1, &matrix1);

  if (operation_code != 3) {
    if (scanf("%d %d", &rows2, &cols2) != 2) {
      printf("n/a\n");
      free(matrix1);
      return 0;
    }
    read_matrix(rows2, cols2, &matrix2);
  }

  switch (operation_code) {
  case 1:
    if (rows1 != rows2 || cols1 != cols2) {
      printf("n/a\n");
      free(matrix1);
      free(matrix2);
      return 0;
    }
    matrix_sum(rows1, cols1, matrix1, matrix2, &result_matrix);
    print_matrix(rows1, cols1, result_matrix);
    break;
  case 2:
    if (cols1 != rows2) {
      printf("n/a\n");
      free(matrix1);
      free(matrix2);
      return 0;
    }
    matrix_multiply(rows1, cols1, rows2, cols2, matrix1, matrix2,
                    &result_matrix);
    print_matrix(rows1, cols2, result_matrix);
    break;
  case 3:
    matrix_transpose(rows1, cols1, matrix1, &result_matrix);
    print_matrix(cols1, rows1, result_matrix);
    break;
  default:
    printf("n/a\n");
    free(matrix1);
    if (operation_code != 3) {
      free(matrix2);
    }
    return 0;
  }

  free(matrix1);
  if (operation_code != 3) {
    free(matrix2);
  }
  free(result_matrix);

  return 0;
}
