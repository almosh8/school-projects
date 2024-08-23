#include <stdio.h>

int largest_prime_divisor(int a);
int is_prime(int n);
int ost(int a, int b);

int main() {
    int a;
    int sc = scanf("%d", &a);
    if (sc != 1) {
        printf("n/a");
        return 0;
    }

    if (a < 0) {
        a = -a;
    }

    printf("%d", largest_prime_divisor(a));
    return 0;
}

int largest_prime_divisor(int a) {
    int largest = 1;
    for (int i = 2; i * i <= a; i++) {
        if (is_prime(i) && ost(a, i) == 0) {
            largest = i;
        }
    }
    return largest;
}

int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        int temp = n;
        while (temp >= i) {
            temp -= i;
        }
        if (temp == 0) {
            return 0;
        }
    }
    return 1;
}

int ost(int a, int b) {
    if (b == 0) {
        return 0;
    }

    int c = 0;

    while (a > 0) {
        a -= b;
        c += 1;
    }

    return -a;
}
