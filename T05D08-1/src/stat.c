#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double count_expected(int *a, int n);
double count_variance(int *a, int n);
void output_result(int max_v, int min_v, double expected_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (!input(data, &n)) {
        printf("n/a\n");
        return 1;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), count_expected(data, n), count_variance(data, n));
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n < 1) {
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int max(int *a, int n) {
    if (n < 1) {
        return 0;
    }
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }
    return max_val;
}

int min(int *a, int n) {
    if (n < 1) {
        return 0;
    }
    int min_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) {
            min_val = a[i];
        }
    }
    return min_val;
}

double count_expected(int *a, int n) {
    if (n < 1) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double count_variance(int *a, int n) {
    if (n < 1) {
        return 0.0;
    }
    double expected_val = count_expected(a, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (a[i] - expected_val) * (a[i] - expected_val);
    }
    return sum / n;
}

void output_result(int max_v, int min_v, double expected_v, double variance_v) {
    printf("%d %d %.6f %.6f\n", max_v, min_v, expected_v, variance_v);
}