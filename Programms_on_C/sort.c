#include <stdio.h>

void read(int *mass) {
    int count = 0;
    while (count < 10) {
        if (scanf("%d", &mass[count]) != 1) {
             break; 
        }
        count++;
    }
        if (count < 10) {
        printf("n/a\n");  
    }
}
void sort(int *mass) {
    for(int j = 0; j < 9; j++) {
        for(int l = 0; l < 9 - j; l++) {
            if (mass[l] > mass[l + 1]) {
                int tmp = mass[l];
                mass[l] = mass[l + 1];
                mass[l + 1] = tmp;
            }
        }
    }
}

void write(int *mass) {
    for (int i = 0; i < 10; i++) {
        printf("%d ", mass[i]);
    }
    printf("\n"); 
}

int main() {
    int mass[10];
    read(mass);
    sort(mass);
    write(mass);
    return 0;
}

