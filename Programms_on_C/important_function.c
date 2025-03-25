#include <stdio.h>
#include <math.h>

int main () {
	double x, y;
	printf("Введите число:\n ");
	scanf("%lf", &x);
	y = 7e-3 * pow(x, 4) + ((22.8* cbrt(x) - 1e3) * x + 3) / (x * x / 2) - x * pow((10 + x), (2/x)) - 1.01;
	printf("%.1lf\n", y);
	return 0;

}
