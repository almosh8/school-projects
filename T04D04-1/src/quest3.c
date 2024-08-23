#include <stdio.h>

long long fibonacci(long long n);

int main() {
    long long a;
    long long sc = scanf("%lld", &a);
    if (sc != 1) {
        printf("n/a");
        return 0;
    }

    printf("%lld", fibonacci(a));
    return 0;
}

long long fibonacci(long long n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}