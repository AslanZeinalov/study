#include <stdio.h>
#include <stdlib.h>

#define NMAX 20

void read_matrix(int N, int M, int **arr) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                printf("n/a\n");
                exit(1);
            }
        }
    }
}

void arr_sum(int N, int M, int **arr, int *sum) {
    for (int i = 0; i < N; i++) {
        sum[i] = 0;
        for (int j = 0; j < M; j++) {
            sum[i] += arr[i][j];
        }
    }
}

void sort_matrix(int N, int **arr, int *sum) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (sum[j] > sum[j + 1]) {
                int temp_sum = sum[j];
                sum[j] = sum[j + 1];
                sum[j + 1] = temp_sum;

                int *temp_row = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp_row;
            }
        }
    }
}

void print_matrix(int N, int M, int **arr) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, N, M;
    if (scanf("%d %d %d", &m, &N, &M) != 3 || N <= 0 || M <= 0 || N > NMAX || M > NMAX) {
        printf("n/a\n");
        return 1;
    }

    int **arr = NULL;
    int *sum = (int *)malloc(N * sizeof(int));

    switch (m) {
        case 1:
            arr = (int **)malloc(N * sizeof(int *));
            for (int i = 0; i < N; i++) {
                arr[i] = (int *)malloc(M * sizeof(int));
            }
            break;
        case 2:
            arr = (int **)malloc(N * sizeof(int *));
            arr[0] = (int *)malloc(N * M * sizeof(int));
            for (int i = 1; i < N; i++) {
                arr[i] = arr[0] + i * M;
            }
            break;
        default:
            printf("n/a\n");
            return 1;
    }

    read_matrix(N, M, arr);
    arr_sum(N, M, arr, sum);
    sort_matrix(N, arr, sum);
    print_matrix(N, M, arr);

    for (int i = 0; i < N; i++) {
        free(arr[i]);
    }
    free(arr);
    free(sum);
    return 0;
}
