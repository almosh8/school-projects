#include <math.h>
#include <stdio.h>

double a(double x);
double b(double x);
double q(double x);

int main() {
    double pi = 2 * acos(0.0);
    double d = pi * 2 / 41;

    for (double x = -pi; x <= pi; x += d) {
        printf("%.7f | ", x);
        if (x == 1) {
            printf("- | ");
        } else {
            printf("%.7f | ", a(x));
        }

        if (1 + 4 * x * x < 0.0 || sqrt(1 + 4 * x * x) - x * x - 1 < 0.0) {
            printf("- | ");
        } else {
            printf("%.7f | ", b(x));
        }

        if (x == 0) {
            printf("-\n");
        } else {
            printf("%.7f\n", q(x));
        }
    }

    return 0;
}

double a(double x) { return 1 / (1 + x * x); }

double b(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }

double q(double x) { return 1 / x / x; }
