#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {
	printf("Введите колличество чисел: \n");
	int n = 0;
	scanf("%d\n", &n);
	printf("Введите массив чисел через пробел: \n");
	int mass[n];
	scanf("%s\n", mass);
	double mat_oj = 0.0;
	double sqr_mat_oj = 0.0;
	double disp = sqr_mat_oj - pow(mat_oj, 2);
	int sum = 0;
	double sqr_sr_arif = pow(((double)sum) /((double)n), 2);
	double sum_sqr = 0.0;
      	double sr_sqr_otcl = sqrt(disp);
	int result = 0;
	for (int j = 0; j <= sizeof(mass)-1; j++){
		mat_oj = mat_oj + mass[j] * (1/n);
		sqr_mat_oj = sqr_mat_oj + pow(mass[j], 2) * 1/n;
		sum = sum + mass[j];
		sum_sqr = sum_sqr + ((double)pow(mass[j], 2));
	}
	for (int o = 0; o <= mass[o]; o++){

		}
	for (int i = 0; i <= sizeof(mass)-1; i++) {
		if (mass[i] % 2 == 0 && mass[i] != 0 && mass[i]>= ((int)mat_oj) && mass[i] >(mat_oj - 3 * sr_sqr_otcl) && mass[i] <  (mat_oj + 3 * sr_sqr_otcl)){
			result = mass[i];
			break;	
		}
	}
	printf("%d", result);
	return 0;
}





