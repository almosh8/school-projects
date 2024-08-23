#include <stdio.h>
#define NMAX 10

int input(int *a, int *n, int *c);
void output(int *a, int n);
void cycle_shift(int *a, int n, int c);

int main() {
    int n, c, data[NMAX];
    if (!input(data, &n, &c)) {
        printf("n/a\n");
        return 1;
    }
    cycle_shift(data, n, c);
    output(data, n);
    return 0;
}

int input(int *a, int *n, int *c) {
    if (scanf("%d", n) != 1 || *n < 1 || *n > NMAX) {
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 0;
        }
    }
    if (scanf("%d", c) != 1 || *n < 1 || *n > NMAX) {
        return 0;
    }
    return 1;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void cycle_shift(int *a, int n, int c) {
    while (c < 0) {
        c += n;
    }
    while (c >= n) {
        c -= n;
    }

    int b[NMAX];
    for (int i = 0; i < n; i++) {
        b[i] = a[(i + c) % n];
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}
