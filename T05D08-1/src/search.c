#include <stdio.h>
#define NMAX 30
#define EPS 1e-9

int input(int *a, int *n);
void calc(int *a, int n, double *expected, double *std_dev);
double count_expected(int *a, int n);
double count_variance(int *a, int n);
double count_std_dev(int *a, int n);
int find_first_match(int *a, int n, double expected, double std_dev);
double sqrt(double x);

int main() {
    int n, data[NMAX];
    double expected, std_dev;
    if (!input(data, &n)) {
        printf("n/a");
        return 0;
    }
    calc(data, n, &expected, &std_dev);
    printf("%d", find_first_match(data, n, expected, std_dev));

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n < 1 || *n > NMAX) {
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void calc(int *a, int n, double *expected, double *std_dev) {
    *expected = count_expected(a, n);
    *std_dev = sqrt(count_std_dev(a, n));
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

double count_std_dev(int *a, int n) { return sqrt(count_variance(a, n)); }

double sqrt(double x) {
    if (x < 0) {
        return 0;
    }

    double low = 0;
    double high = x;

    while (high - low > EPS) {
        double mid = (low + high) / 2;
        if (mid * mid > x) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return low;
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

int find_first_match(int *a, int n, double expected, double std_dev) {
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] >= expected && expected - 3 * std_dev <= a[i] &&
            a[i] <= expected + 3 * std_dev && a[i] != 0) {
            return a[i];
        }
    }
    return 0;
}
