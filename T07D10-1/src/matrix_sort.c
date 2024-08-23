#include <stdio.h>
#include <stdlib.h>

void handle_matrix(int **matrix, int rows, int cols);
int input_matrix(int **matrix, int rows, int cols);
void output_matrix(int **matrix, int rows, int cols);
void free_matrix(int **matrix, int rows);
void sort_matrix(int **matrix, int rows, int cols);

int main() {
    int rows, cols, choice;
    int **dynamic_matrix;

    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("n/a");
        return 0;
    }

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("n/a");
        return 0;
    }

    switch (choice) {
        case 1:
            dynamic_matrix = (int **)calloc(rows, sizeof(int *));
            for (int i = 0; i < rows; i++) {
                dynamic_matrix[i] = (int *)calloc(cols, sizeof(int));
            }

            handle_matrix(dynamic_matrix, rows, cols);
            break;

        case 2:
            dynamic_matrix = (int **)malloc(rows * sizeof(int *));
            if (dynamic_matrix == NULL) {
                printf("n/a");
                return 0;
            }
            for (int i = 0; i < rows; i++) {
                dynamic_matrix[i] = (int *)calloc(cols, sizeof(int));
            }

            handle_matrix(dynamic_matrix, rows, cols);

            break;

        case 3:
            dynamic_matrix = (int **)malloc(rows * sizeof(int *));
            if (dynamic_matrix == NULL) {
                printf("n/a");
                return 0;
            }
            for (int i = 0; i < rows; i++) {
                dynamic_matrix[i] = (int *)malloc(cols * sizeof(int));
            }
            handle_matrix(dynamic_matrix, rows, cols);

            break;
    }

    return 0;
}

void handle_matrix(int **matrix, int rows, int cols) {
    if (matrix == NULL) {
        printf("n/a");
        return;
    }
    if (!input_matrix(matrix, rows, cols)) {
        printf("n/a");
        free_matrix(matrix, rows);
        return;
    }
    sort_matrix(matrix, rows, cols);
    output_matrix(matrix, rows, cols);
    free_matrix(matrix, rows);
}

int input_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

void output_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j != cols - 1) printf(" ");
        }
        if (i != rows - 1) printf("\n");
    }
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void sort_matrix(int **matrix, int rows, int cols) {
    int *row_sums = (int *)malloc(rows * sizeof(int));
    if (row_sums == NULL) {
        printf("n/a");
        return;
    }

    // Calculate row sums
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
        row_sums[i] = sum;
    }

    // Sort rows based on row sums
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (row_sums[j] > row_sums[j + 1]) {
                // Swap rows
                int temp_sum = row_sums[j];
                row_sums[j] = row_sums[j + 1];
                row_sums[j + 1] = temp_sum;

                for (int k = 0; k < cols; k++) {
                    int temp = matrix[j][k];
                    matrix[j][k] = matrix[j + 1][k];
                    matrix[j + 1][k] = temp;
                }
            }
        }
    }

    free(row_sums);
}
