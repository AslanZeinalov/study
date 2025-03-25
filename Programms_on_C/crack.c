#include <stdio.h>

int main() {
	double x, y;
do {

	printf("Введите координаты: ");
		scanf("%lf %lf", &x, &y);
	if((x*x+y*y) < 25){
		printf("GOTCHA\n");
	}else {
		printf("MISS\n");
	}
	}while((x*x+y*y)>=25);
	return 0;
}
