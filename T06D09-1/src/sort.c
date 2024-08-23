#include <stdio.h>
#define N 10

int input(int *a, int n);
void sort(int *a, int n);
void output(int *a, int n);

int main() {
    int data[N];
    if (!input(data, N)) {
        printf("n/a");
        return 0;
    }
    sort(data, N);
    output(data, N);

    return 0;
}

int input(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
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
        printf("%d ", a[i]);
    }
}