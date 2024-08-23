#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }

    char mode = *argv[1];
    if (mode == '0') {
        char c, c1;
        while (1) {
            scanf("%c%c", &c, &c1);
            if (c1 != ' ' && c1 != '\n') {
                printf("n/a");
                return 0;
            }
            printf("%02X ", c);
            if (c1 == '\n') {
                break;
            }
        }
    } else if (mode == '1') {
        int c;
        char c1;
        while (1) {
            scanf("%02x%c", &c, &c1);
            if (c1 != ' ' && c1 != '\n') {
                printf("n/a");
                return 0;
            }
            printf("%c ", (char)c);
            if (c1 == '\n') {
                break;
            }
        }
    } else {
        printf("n/a");
    }
    return 0;
}