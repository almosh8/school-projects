#include <stdio.h>

#define LEN 100

int input(int *a, int *n);
void output(int *a, int n);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

int main() {
    int na, nb, a[LEN], b[LEN], c[LEN + 1];
    if (!input(a, &na) || !input(b, &nb)) {
        printf("n/a");
        return 1;
    }

    int result_length;
    sum(a, na, b, nb, c, &result_length);
    output(c, result_length);
    printf("\n");

    sub(a, na, b, nb, c, &result_length);
    if (result_length == 0)
        printf("n/a");
    else
        output(c, result_length);

    return 0;
}

int input(int *a, int *n) {
    int c;
    *n = 0;

    while (1) {
        c = getchar();
        if (c >= '0' && c <= '9') {
            if (*n < LEN) {
                a[*n] = c - '0';
                (*n)++;
            } else {
                return 0;
            }
        } else {
            return 0;
        }

        c = getchar();
        if (c == '\n') break;
        if (c == ' ') continue;
        return 0;
    }

    if (*n > 0) {
        return 1;
    }
    return 0;
}

void output(int *a, int n) {
    int leading_zero = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] != 0 || i == 0) {
            leading_zero = 0;
        }
        if (!leading_zero) {
            printf("%d ", a[i]);
        }
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int carry = 0;
    *result_length = (len1 > len2) ? len1 : len2;
    for (int i = 0; i < *result_length || carry; i++) {
        result[i] = carry;
        if (i < len1) {
            result[i] += buff1[len1 - i - 1];
        }
        if (i < len2) {
            result[i] += buff2[len2 - i - 1];
        }
        carry = result[i] / 10;
        result[i] %= 10;
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int borrow = 0;
    *result_length = len1;
    for (int i = 0; i < len1; i++) {
        result[i] = buff1[len1 - i - 1] - borrow;
        if (i < len2) {
            result[i] -= buff2[len2 - i - 1];
        }
        if (result[i] < 0) {
            result[i] += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }

    while (*result_length > 0 && result[*result_length - 1] == 0) {
        (*result_length)--;
    }

    if (borrow || len1 < len2) {
        *result_length = 0;
    }
}
