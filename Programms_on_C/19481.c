#include <stdio.h>

int max_fun(int n) {
    int max = 0; // переменная для хранения максимального простого делителя
    for (int i = 2; i <= n; i++) {
        // Проверяем, является ли i делителем числа n
        if (n % i == 0) {
            max = i; // обновляем максимальный делитель
            // Делаем деление n, пока это возможно
            while (n % i == 0) {
                n /= i; 
            }
        }
    }
    return max; // возвращаем максимальный простой делитель
}

int main() {
    int n = 0;

    printf("Введите число: \n");
    scanf("%d", &n);
    
    if (n > 0) {
        int max = max_fun(n); // получаем максимальный простой делитель
        printf("Максимальный простой делитель: %d\n", max);
    } else if (n < 0) {
        n = -n; // если число отрицательное, делаем его положительным
        int max = max_fun(n);
        printf("Максимальный простой делитель: %d\n", max);
    } else {
        printf("n/a"); // обрабатываем ситуацию, когда n равно нулю
    }
    
    return 0;
}
