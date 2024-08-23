#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

void handle_dynamic(int **matrix, int rows, int cols);
int input_static(int (*matrix)[MAX_SIZE], int rows, int cols);
int input_dynamic(int **matrix, int rows, int cols);
void output_static(int (*matrix)[MAX_SIZE], int rows, int cols);
void output_dynamic(int **matrix, int rows, int cols);
void free_dynamic(int **matrix, int rows);

int main() {
    int rows, cols, choice;
    int **dynamic_matrix1, **dynamic_matrix2, **dynamic_matrix3;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("n/a");
        return 0;
    }

    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("n/a");
        return 0;
    }

    switch (choice) {
        case 1:
            int matrix[MAX_SIZE][MAX_SIZE];
            if (rows > MAX_SIZE || cols > MAX_SIZE || !input_static(matrix, rows, cols)) {
                printf("n/a");
                return 0;
            }
            output_static(matrix, rows, cols);
            break;

        case 2:
            dynamic_matrix1 = (int **)malloc(rows * sizeof(int *));
            for (int i = 0; i < rows; i++) {
                dynamic_matrix1[i] = (int *)calloc(cols, sizeof(int));
            }

            handle_dynamic(dynamic_matrix1, rows, cols);
            break;

        case 3:
            dynamic_matrix2 = (int **)malloc(rows * sizeof(int *));
            if (dynamic_matrix2 == NULL) {
                printf("n/a");
                return 0;
            }
            for (int i = 0; i < rows; i++) {
                dynamic_matrix2[i] = (int *)calloc(cols, sizeof(int));
            }

            handle_dynamic(dynamic_matrix2, rows, cols);

            break;

        case 4:
            dynamic_matrix3 = (int **)malloc(rows * sizeof(int *));
            if (dynamic_matrix3 == NULL) {
                printf("n/a");
                return 0;
            }
            for (int i = 0; i < rows; i++) {
                dynamic_matrix3[i] = (int *)malloc(cols * sizeof(int));
            }
            handle_dynamic(dynamic_matrix3, rows, cols);

            break;
    }

    return 0;
}

void handle_dynamic(int **matrix, int rows, int cols) {
    if (matrix == NULL) {
        printf("n/a");
        return;
    }
    if (!input_dynamic(matrix, rows, cols)) {
        printf("n/a");
        free_dynamic(matrix, rows);
        return;
    }
    output_dynamic(matrix, rows, cols);
    free_dynamic(matrix, rows);
}

int input_static(int (*matrix)[MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 0;
}

int input_dynamic(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 0;
}

void output_static(int (*matrix)[MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j != cols - 1) printf(" ");
        }
        if (i != rows - 1) printf("\n");
    }
}

void output_dynamic(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j != cols - 1) printf(" ");
        }
        if (i != rows - 1) printf("\n");
    }
}

void free_dynamic(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}