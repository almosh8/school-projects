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
    int seed = 0, speed = 11;
    printf("Enter game speed(number from 1(the fastest) to 10(the slowest))\n");
    scanf("%d", &speed);
    printf("Enter initial matrix\n");

    int **field = init_matrix();
    fill_matrix(field);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d ", field[i][j]);
        }
        printf("\n");
    }

    while (1) {
        draw(field);
        int **new = init_matrix();
        update_field(field, new);

        free_matrix(field);
        field = new;
        for (int j = 0; j < speed * 10000000; j++) {
            seed++;
        }
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
            printf("%c", field[i][j] ? 'C' : '0');
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
    int n = 0, s = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int dx = (x + d[i] + ROWS) % ROWS;
            int dy = (y + d[j] + COLS) % COLS;
            if (!(dx == x && dy == y)) {
                s += field[dx][dy];
                n++;
            }
        }
    }

    // live cell
    if (field[x][y] == 1) {
        if (s < 2) return 0;
        if (s > 3) return 0;
        return 1;
    }

    // dead cell
    if (s == 3) return 1;
    return 0;
}

void free_matrix(int **matrix) {
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
