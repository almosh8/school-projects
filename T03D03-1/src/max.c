#include <stdio.h>

int max(int x, int y);

int main() {
    int x, y;

    int sc;
    sc = scanf("%d %d", &x, &y);
    if (sc != 2) {
        printf("n/a");
        return 0;
    }

    printf("%d", (int)max(x, y));
    return 0;
}

int max(int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}
