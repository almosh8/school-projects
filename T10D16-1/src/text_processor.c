#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc < 2 || s21_strcmp(argv[1], "-w") != 0) {
        printf("n/a");
        return 0;
    }
    int line_width;
    if (scanf("%d\n", &line_width) != 1 || line_width < 1) {
        printf("n/a");
        return 0;
    }

    char input[MAX_LINE_LENGTH] = {0};

    if (fgets(input, MAX_LINE_LENGTH, stdin) == NULL) {
        printf("n/a");
        return 0;
    }

    char *word = s21_strtok(input, " \n");
    char output[MAX_LINE_LENGTH] = {0};
    int output_len = 0;

    while (word != NULL) {
        int word_len = s21_strlen(word);
        if ((output_len == 0 && output_len + word_len <= line_width) ||
            output_len + word_len + 1 <= line_width) {
            if (output_len > 0) {
                putchar(' ');
            }
            printf("%s", word);
            s21_strcpy(output + output_len, word);
            output_len += word_len;
        } else {
            if (line_width == 1 && word_len > 1) {
                printf("n/a");
                return 0;
            }

            if (word_len > line_width) {
                int i = 0;
                while (i < word_len) {
                    if (i + line_width >= word_len) {
                        for (; i < word_len; i++) {
                            putchar(word[i]);
                        }
                        output_len = word_len;
                    } else {
                        if (output_len >= line_width - 2) {
                            putchar('\n');
                            output_len = 0;
                            continue;
                        } else if (output_len > 0) {
                            putchar(' ');
                            output_len++;
                        }

                        for (int j = 0; j + output_len < line_width - 1; j++) {
                            putchar(word[i + j]);
                        }
                        putchar('-');
                        putchar('\n');
                        i += line_width - 1 - output_len;
                        output_len = 0;
                    }
                }
            } else {
                printf("\n%s", word);
                output_len = word_len;
            }
        }
        word = s21_strtok(NULL, " \n");
    }

    return 0;
}
