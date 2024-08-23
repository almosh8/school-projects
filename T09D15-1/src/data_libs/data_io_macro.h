#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#define GENERATE_IO_FUNCTIONS
#ifdef TYPE_INT
void input(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            a[i] = -1;
        }
    }
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
#endif

#ifdef TYPE_LONG_LONG
void input(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1) {
            a[i] = -1;
        }
    }
}

void output(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");
}
#endif

#ifdef TYPE_FLOAT
void input(float *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%f", &a[i]) != 1) {
            a[i] = -1.0f;
        }
    }
}

void output(float *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
}
#endif

#ifdef TYPE_DOUBLE
void input(double *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &a[i]) != 1) {
            a[i] = -1.0;
        }
    }
}

void output(double *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
}
#endif

#ifdef TYPE_LONG_DOUBLE
void input(long double *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%Lf", &a[i]) != 1) {
            a[i] = -1.0L;
        }
    }
}

void output(long double *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%Lf ", a[i]);
    }
    printf("\n");
}
#endif
#endif