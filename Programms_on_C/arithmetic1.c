#include<stdio.h>
int main (){
    
    
        printf("Введите 2 числа: ");
        double a;
    double b;
        scanf("%lf %lf", &a, &b);
        int sm = a + b;
    int mn = a - b;
    int ymn = a * b;
    int dl = a / b;
    if (a==((double)((int)a))&& b == (double)((int)b)){
        printf("%d %d %d ", sm, mn, ymn);
    
            if(b != 0){
                printf("%d", dl);
            }else {printf("n/a");}
            }else {printf("n/a");}
       
        return 0;
}
