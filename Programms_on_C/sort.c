#include <stdio.h>
#include <stdlib.h>

int read(int n, int *mass) {
	for (int k = 0; k < n; k++) {
		if (scanf("%d", &mass[k]) != 1) {
			printf("n/a\n");
			return 1;
		}
	}
	printf("\n");
	return 1;
}
void sort(int *mass, int n) {
    for(int j = 0; j < n - 1; j++) {
        for(int l = 0; l < n -1; l++) {
            if (mass[l] > mass[l + 1]) {
                int tmp = mass[l];
                mass[l] = mass[l + 1];
                mass[l + 1] = tmp;
            }
        }
    }
}

void write(int *mass, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", mass[i]);
    }
    printf("\n");
  }

int main() {
	int* mass;
	int n;
    	if (scanf("%d", &n) != 1) {
		printf("n/a\n");
	}
	mass = (int*)malloc(n * sizeof(int));
	if (mass == NULL){
		printf("n/a");
		return 1;
	}
    	read(n, mass);
    	sort(mass, n);
    	write(mass, n);
	free(mass);
    	return 0;
}

