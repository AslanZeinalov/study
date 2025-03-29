#include <stdio.h>
#include <math.h>

int main() {
    double x = 0;
    double pi = 3.1415926;
    double iteration = 3.1415926 * 2 / 42;
    for (int i = 0; i <= 42; i++) {
        x = -1 * pi + iteration * i;
        double y1, y2, y3;
        char y1_str[10], y2_str[10], y3_str[10];
        if (1 + x * x == 0) {
            snprintf(y1_str, sizeof(y1_str), "-");
        } else {
            y1 = 1 / (1 + x * x);
            snprintf(y1_str, sizeof(y1_str), "%.7lf", y1);
        }
        double inner_sqrt = 1 + 4 * x * x * (1 - x * x - 1);
        if (inner_sqrt < 0) {
            snprintf(y2_str, sizeof(y2_str), "-");
        } else {
            y2 = sqrt(sqrt(inner_sqrt));
            snprintf(y2_str, sizeof(y2_str), "%.7lf", y2);
        }
        if (x == 0) {
            snprintf(y3_str, sizeof(y3_str), "-");
        } else {
            y3 = 1 / (x * x);
            snprintf(y3_str, sizeof(y3_str), "%.7lf", y3);
        }
        printf("%.7lf | %s | %s | %s\n", x, y1_str, y2_str, y3_str);
    }
    return 0;
}
