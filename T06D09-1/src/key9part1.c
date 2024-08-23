/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define NMAX 10

void input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int buffer[NMAX];
    int length;

    input(buffer, &length);
    if (length == -1 || length > NMAX) {
        printf("n/a");
        return 0;
    }

    int sum;
    sum = sum_numbers(buffer, length);
    if (sum == -1) {
        printf("n/a");
        return 0;
    }
    printf("%d\n", sum);

    int numbers[NMAX];
    int n;
    n = find_numbers(buffer, length, sum, numbers);
    for (int i = 0; i < n; i++) printf("%d ", numbers[i]);

    return 0;
}

void input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length < 1 || *length > NMAX) {
        *length = -1;
        return;
    }
    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &buffer[i]) != 1) {
            *length = -1;
            return;
        }
    }
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;
    int f = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
            f = 1;
        }
    }

    if (f) return sum;
    return -1;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int n = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[n] = buffer[i];
            n++;
        }
    }

    return n;
}
