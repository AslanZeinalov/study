#include <stdio.h>

int main ()
{
	int a, b, c;
	printf("Введите 2 числа: ");
	scanf("%d %d", &a, &b);
	c = a + b;
	printf("%d + %d = %d", a, b, c);
	return 0;

}
