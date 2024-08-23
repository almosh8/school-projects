#include <math.h>
#include <stdio.h>

double a(double x);
double b(double x);
double q(double x);

int main() {
    double pi = 2 * acos(0.0);
    double d = pi * 2 / 41;

    printf("The witch of Agnesi with diameter one:\n");
    for (double x = -pi; x <= pi; x += d) {
        double y;
        if (x == 1)
            y = -1;
        else
            y = a(x);
        for (int i = 0; i < 21; i++) {
            if (i == (int)y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("The lemniscate of Bernoulli with a unit interval in the positive half-plane:\n");
    for (double x = -pi; x <= pi; x += d) {
        double y;
        if (1 + 4 * x * x < 0.0 || sqrt(1 + 4 * x * x) - x * x - 1 < 0.0)
            y = -1;
        else
            y = b(x);
        for (int i = 0; i < 21; i++) {
            if (i == (int)y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Quadratic hyperbola:\n");
    for (double x = -pi; x <= pi; x += d) {
        double y;
        if (x == 1)
            y = -1;
        else
            y = q(x);
        for (int i = 0; i < 21; i++) {
            if (i == (int)y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}

double a(double x) { return 1 / (1 + x * x); }

double b(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }

double q(double x) { return 1 / x / x; }
