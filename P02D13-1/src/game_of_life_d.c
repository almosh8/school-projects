#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 80

void draw(int **field);
void update_field(int **field, int **new);
int cell_state(int **field, int x, int y);
int **init_matrix();
void fill_matrix(int **field);
void free_matrix(int **matrix);

int main() {
    int speed = 11;
    printf("Enter game speed(number from 1(the fastest) to 10(the slowest))\n");
    scanf("%d", &speed);
    printf("Enter initial matrix (0 for dead, 1 for 'C', 2 for 'B')\n");

    int **field = init_matrix();
    fill_matrix(field);

    while (1) {
        draw(field);
        int **new = init_matrix();
        update_field(field, new);

        free_matrix(field);
        field = new;
        for (int j = 0; j < speed * 10000000; j++)
            ;
        system("clear");  // Очистка терминала
    }
    free_matrix(field);
}

int **init_matrix() {
    int **a = calloc(ROWS, sizeof(int *));
    for (int i = 0; i < ROWS; ++i) {
        a[i] = calloc(COLS, sizeof(int));
    }
    return a;
}

void fill_matrix(int **field) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            scanf("%d", &field[i][j]);
        }
    }
}

void draw(int **field) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%c", field[i][j] == 1 ? 'O' : (field[i][j] == 2 ? 'X' : ' '));
        }
        printf("\n");
    }
    printf("\n");
}

void update_field(int **field, int **new) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            new[i][j] = cell_state(field, i, j);
        }
    }
}

int cell_state(int **field, int x, int y) {
    int d[3] = {0, -1, 1};
    int s1 = 0, s2 = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int dx = (x + d[i] + ROWS) % ROWS;
            int dy = (y + d[j] + COLS) % COLS;
            if (!(dx == x && dy == y)) {
                if (field[dx][dy] == 1) s1++;
                if (field[dx][dy] == 2) s2++;
            }
        }
    }

    if (field[x][y] == 1) {
        if (s1 < 2) return 0;
        if (s1 > 3) return 0;
        return 1;
    }

    if (field[x][y] == 2) {
        if (s2 < 2) return 0;
        if (s2 > 3) return 0;
        return 2;
    }

    if (s1 == 3) return 1;
    if (s2 == 3) return 2;
    return 0;
}

void free_matrix(int **matrix) {
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}