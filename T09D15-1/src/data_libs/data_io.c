#include "data_io.h"

#include <stdio.h>

void input(double *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &a[i]) != 1) {
            a[i] = -1;
        }
    }
}

void output(double *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf ", a[i]);
    }
}