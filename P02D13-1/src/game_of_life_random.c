#include <stdio.h>
#include <stdlib.h>

#define ROWS 25  // Определение количества строк в игровом поле
#define COLS 80  // Определение количества столбцов в игровом поле

void draw(int **field);  // Функция для отрисовки игрового поля
void update_field(int **field, int **new);  // Функция для обновления игрового поля
int cell_state(int **field, int x, int y);  // Функция для определения состояния клетки
int **init_matrix();  // Функция для инициализации матрицы игрового поля
void fill_matrix(int **field, int fr);  // Функция для заполнения матрицы случайными значениями
void free_matrix(int **matrix);  // Функция для освобождения памяти, выделенной под матрицу

int main() {
    int seed, speed, fr;
    printf("Enter seed for random field generation\n");  // Запрос на ввод сида для генерации случайных чисел
    scanf("%d", &seed);
    srand(seed);  // Инициализация генератора случайных чисел
    printf(
        "Enter game speed(number from 1(the fastest) to 10(the slowest))\n");  // Запрос на ввод скорости игры
    scanf("%d", &speed);
    printf(
        "Enter frequency of live cells(number from 1(the most frequent) to 10(the least frequent))\n");  // Запрос
                                                                                                         // на
                                                                                                         // ввод
                                                                                                         // частоты
                                                                                                         // жизни
                                                                                                         // клеток
    scanf("%d", &fr);

    int **field = init_matrix();  // Инициализация игрового поля
    fill_matrix(field, fr);  // Заполнение игрового поля случайными значениями

    while (1) {
        draw(field);  // Отрисовка текущего состояния игрового поля
        int **new = init_matrix();  // Создание нового игрового поля для обновления
        update_field(field, new);  // Обновление состояния игрового поля
        free_matrix(field);  // Освобождение памяти, выделенной под старое игровое поле
        field = new;  // Присваивание нового игрового поля старому
        for (int j = 0; j < speed * 10000000; j++) {
            seed++;
        }
        system("clear");  // Очистка терминала
    }
    free_matrix(field);  // Освобождение памяти, выделенной под игровое поле
}

int **init_matrix() {
    int **a = calloc(ROWS, sizeof(int *));  // Выделение памяти для массива указателей на строки
    for (int i = 0; i < ROWS; ++i) {
        a[i] = calloc(COLS, sizeof(int));  // Выделение памяти для каждой строки
    }
    return a;  // Возвращение матрицы
}

void fill_matrix(int **field, int fr) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            field[i][j] = (rand() % fr) ? 0 : 1;  // Заполнение матрицы случайными значениями 0 или 1
        }
    }
}

void draw(int **field) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%c", field[i][j]
                             ? '$'
                             : ' ');  // Отрисовка игрового поля, где '$' - живая клетка, ' ' - мертвая клетка
        }
        printf("\n");
    }
    printf("\n");
}

void update_field(int **field, int **new) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            new[i][j] = cell_state(field, i, j);  // Обновление состояния каждой клетки
        }
    }
}

int cell_state(int **field, int x, int y) {
    int d[3] = {0, -1, 1};
    int s = 0;  // int n = 0, s = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int dx = (x + d[i] + ROWS) %
                     ROWS;  // int dx = x + d[i]; Вычисление координаты соседа с учетом обертывания
            int dy = (y + d[j] + COLS) %
                     COLS;  // int dy = y + d[j]; Вычисление координаты соседа с учетом обертывания
            if (!(dx == x && dy == y)) {
                s += field[dx][dy];  // Подсчет количества живых соседей
                // if (0 <= dx && dx < ROWS && 0 <= dy && dy < COLS && !(dx == x && dy == y)) {
                // s += field[dx][dy];
                // n++;
            }
        }
    }

    // Живая клетка
    if (field[x][y] == 1) {
        if (s < 2) return 0;  // Если живых соседей меньше двух, клетка умирает
        if (s > 3) return 0;  // Если живых соседей больше трех, клетка умирает
        return 1;             // Иначе клетка остается живой
    }

    // Мёртвая клетка
    if (s == 3) return 1;  // Если ровно три живых соседа, клетка оживает
    return 0;              // Иначе клетка остается мертвой
}

void free_matrix(int **matrix) {
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);  // Освобождение памяти, выделенной под каждую строку
    }
    free(matrix);  // Освобождение памяти, выделенной под массив указателей на строки
}