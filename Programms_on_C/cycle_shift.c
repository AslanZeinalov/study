#include <stdio.h>

#define MAX_SIZE 100

void read(int *arr, int n) {
    for (int r = 0; r < n; r++) {
        scanf("%d", &arr[r]);
    }
}
void cycle_shift(int *arr, int n, int c) {
    if (n <= 0 || c < -n || c > n) {
        printf("n/a\n");
        return;
    }
    if (c < 0) {
        c = (c + n) % n;
    } else {
        c = c % n;
    }
     int result[MAX_SIZE];
        for (int i = 0; i < n; i++) {
        result[i] = arr[(i + c) % n];
    }
       for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }
}
void write(int *arr, int n) {
    for (int w = 0; w < n; w++) {
        printf("%d ", arr[w]);
    }
    printf("\n");
}
int main() {
    int n, c;
    int arr[MAX_SIZE];
    printf("Введите размер массива: \n");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_SIZE) {
        printf("n/a\n");
        return 0;
    }
    printf("Введите элементы массива через пробел: \n");
    read(arr, n);
    printf("Введите величину сдвига: \n");
    scanf("%d", &c);
    cycle_shift(arr, n, c);
    write(arr, n);
    return 0;
}

