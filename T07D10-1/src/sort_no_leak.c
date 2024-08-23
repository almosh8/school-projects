#include <stdio.h>
#include <stdlib.h>

int input(int **a, int *n);
void sort(int *a, int n);
void output(int *a, int n);

int main() {
    int n, *data;
    if (!input(&data, &n)) {
        printf("n/a");
        return 0;
    }
    sort(data, n);
    output(data, n);
    free(data);

    return 0;
}

int input(int **a, int *n) {
    if (scanf("%d", n) != 1 || *n <= 0) {
        return 0;
    }
    *a = (int *)malloc(*n * sizeof(int));
    if (*a == NULL) {
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &(*a)[i]) != 1) {
            free(*a);
            return 0;
        }
    }
    return 1;
}

void sort(int *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d%c", a[i], i == n - 1 ? '\0' : ' ');
    }
}
