#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

void read1(int arr[NMAX][NMAX]) {
    // Для статического массива можно оставить пустым или добавить функциональность.
}

int read2(int ***arr, int L, int H) {
    *arr = (int **)malloc(L * sizeof(int *));
    if (*arr == NULL) return 1;

    for (int i = 0; i < L; i++) {
        (*arr)[i] = (int *)malloc(H * sizeof(int));
        if ((*arr)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*arr)[j]);
            }
            free(*arr);
            return 1;
        }
    }
    return 0;
}

int read3(int ***arr, int L, int H) {
    *arr = (int **)calloc(L, sizeof(int *));
    if (*arr == NULL) return 1;
    for (int i = 0; i < L; i++) {
        (*arr)[i] = (int *)calloc(H, sizeof(int));
        if ((*arr)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*arr)[j]);
            }
            free(*arr);
            return 1;
        }
    }
    return 0;
}

void input(int L, int H, int **arr) {
    for (int b = 0; b < L; b++) {
        for (int v = 0; v < H; v++) {
            scanf("%d", &arr[b][v]);
        }
    }
}
void write(int **arr, int L, int H) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < H; j++) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", arr[i][j]);
        }
        printf("\n"); 
    }
}
void min_func(int **minArr, int H, int L, int **arr) {
    *minArr = (int*)calloc(H, sizeof(int));
    if (*minArr == NULL) return;

    for (int i = 0; i < H; i++) {
        int mini = arr[0][i]; // Инициализация с первым элементом строки.
        for (int j = 1; j < L; j++) {
            if (arr[j][i] < mini) {
                mini = arr[j][i];
            }
        }
        (*minArr)[i] = mini;
    }
}

void max_func(int **maxArr, int L, int H, int **arr) {
    *maxArr = (int*)calloc(L, sizeof(int));
    if (*maxArr == NULL) return;

    for (int i = 0; i < L; i++) {
        int maxi = arr[i][0]; // Инициализация с первым элементом строки.
        for (int j = 1; j < H; j++) {
            if (arr[i][j] > maxi) {
                maxi = arr[i][j];
            }
        }
        (*maxArr)[i] = maxi;
    }
}

int main() {
    	int **arr;
    	int m, L, H;
	if (scanf("%d", &m) != 1 || m < 1 || m > 4) {
        printf("n/a\n");
        return 1;
    	}
   	if (scanf("%d %d", &L, &H) != 2 || L <= 0 || H <= 0 || L > NMAX || H > NMAX) {
        printf("n/a\n");
        return 1;
   	}
    	switch (m) {
        case 1: {
            int static_arr[NMAX][NMAX];
            read1(static_arr);
            arr = (int **)malloc(L * sizeof(int *)); 
            for (int i = 0; i < L; i++) {
                arr[i] = static_arr[i]; 
            }
            break;
        }
        case 2:
            if (read2(&arr, L, H) != 0) {
                printf("n/a\n");
                return 1;
            }
            break;
        case 3:
            if (read3(&arr, L, H) != 0) {
                printf("n/a\n");
                return 1;
            }
            break;
      	}
    input(L, H, arr);
    write(arr, L, H);
    
    int *minArr = NULL;
    int *maxArr = NULL;
    max_func(&maxArr, L, H, arr);
    min_func(&minArr, H, L, arr);
    
    for (int i = 0; i < L; i++) {
        printf("%d ", maxArr[i]);
    }
    printf("\n");
  
    for (int i = 0; i < H; i++) {
        printf("%d ", minArr[i]);
    }
   
	free(minArr);
	free(maxArr);
      for (int i = 0; i < L; i++) {
		free(arr[i]);
      }

	return 0;
 }

