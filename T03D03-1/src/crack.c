#include <stdio.h>

int main() {
    float x, y;
    int sc;

    sc = scanf("%f %f", &x, &y);
    if (sc != 2) {
        printf("n/a");
        return 0;
    }

    if (x * x + y * y < 25.0) {
        printf("GOTCHA");
    } else {
        printf("MISS");
    }

    return 0;
}