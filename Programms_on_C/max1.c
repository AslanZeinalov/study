#include <stdio.h>
	
double a = 0;
double b = 0;
int max(int a, int b){
	if(a>b){
		return a;
	}else {
		return b;
	}
}

int main () {
	do {
	printf("Введите 2 числа: ");
	scanf("%lf %lf", &a, &b);
	if(max(a, b) != 0 && (int)a == a && (int)b == b) {
	printf("Максимальное число: %d\n", max(a, b));
	} else {
		printf("n/a\n");
	}
	} while(a != -9999);	
	return 0;
}


//программа работает как надо за исключением случая когда макс число - 0.
//пока не знаю как это исправить, вернусь попозже
