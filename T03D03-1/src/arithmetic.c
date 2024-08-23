#include <stdio.h>

int main() {
    int x, y;

    int sc;
    sc = scanf("%d %d", &x, &y);
    if (sc != 2) {
        printf("n/a n/a n/a n/a");
        return 0;
    }

    printf("%d %d %d ", x + y, x - y, x * y);
    if (y != 0) {
        printf("%d", x / y);
    } else {
        printf("n/a");
    }
    return 0;
}
