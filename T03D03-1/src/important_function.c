#include <math.h>
#include <stdio.h>

long double f(long double x);

int main() {
    long double x;
    int sc;
    sc = scanf("%Lf", &x);
    if (sc != 1) {
        printf("n/a");
        return 0;
    }
    printf("%.1Lf", f(x));
    return 0;
}

long double f(long double x) {
    return 0.007 * pow(x, 4) + ((22.8 * pow(x, 1.0 / 3.0) - 1000) * x + 3) / (x * x / 2) -
           x * pow(10 + x, 2.0 / x) - 1.01;
}
