#include <stdio.h>
#include <stdlib.h>

int input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);
int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int transpose(int **matrix, int n, int m, int **matrix_result);
int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
void free_matrix(int **matrix, int rows);

int main() {
    int operation, rows1, cols1, rows2, cols2;
    int **matrix1, **matrix2, **result;

    if (scanf("%d", &operation) != 1 || (operation < 1 || operation > 3)) {
        printf("n/a");
        return 0;
    }

    switch (operation) {
        case 1:  // Addition

            if (scanf("%d %d", &rows1, &cols1) != 2 || rows1 <= 0 || cols1 <= 0) {
                printf("n/a");
                return 0;
            }

            result = (int **)malloc(rows1 * sizeof(int *));
            if (result == NULL) {
                printf("n/a");
                free_matrix(result, rows1);
                return 0;
            }

            matrix1 = (int **)malloc(rows1 * sizeof(int *));
            if (matrix1 == NULL) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, rows1);
                return 0;
            }

            if (!input(matrix1, &rows1, &cols1)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, rows1);
                return 0;
            }

            if (scanf("%d %d", &rows2, &cols2) != 2 || rows2 <= 0 || cols2 <= 0 || cols1 != rows2) {
                printf("n/a");
                return 0;
            }

            matrix2 = (int **)malloc(rows2 * sizeof(int *));
            if (matrix2 == NULL) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(matrix2, rows2);
                free_matrix(result, rows1);
                return 0;
            }

            if (!input(matrix2, &rows2, &cols2)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(matrix2, rows2);
                free_matrix(result, rows1);
                return 0;
            }

            if (!sum(matrix1, rows1, cols1, matrix2, rows2, cols2, result, &rows1, &cols1)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(matrix2, rows2);
                free_matrix(result, rows1);
                return 0;
            }

            output(result, rows1, cols1);
            free_matrix(matrix1, rows1);
            free_matrix(matrix2, rows2);
            free_matrix(result, rows1);
            break;

        case 2:  // Multiplication

            if (scanf("%d %d", &rows1, &cols1) != 2 || rows1 <= 0 || cols1 <= 0) {
                printf("n/a");
                return 0;
            }

            result = (int **)malloc(rows1 * sizeof(int *));
            if (result == NULL) {
                printf("n/a");
                free_matrix(result, rows1);
                return 0;
            }

            matrix1 = (int **)malloc(rows1 * sizeof(int *));
            if (matrix1 == NULL) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, rows1);
                return 0;
            }

            if (!input(matrix1, &rows1, &cols1)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, rows1);
                return 0;
            }

            if (scanf("%d %d", &rows2, &cols2) != 2 || rows2 <= 0 || cols2 <= 0 || cols1 != rows2) {
                printf("n/a");
                return 0;
            }

            matrix2 = (int **)malloc(rows2 * sizeof(int *));
            if (matrix2 == NULL) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(matrix2, rows2);
                free_matrix(result, rows1);
                return 0;
            }

            if (!input(matrix2, &rows2, &cols2)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(matrix2, rows2);
                free_matrix(result, rows1);
                return 0;
            }

            if (!mul(matrix1, rows1, cols1, matrix2, rows2, cols2, result, &rows1, &cols2)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(matrix2, rows2);
                free_matrix(result, rows1);
                return 0;
            }

            output(result, rows1, cols2);
            free_matrix(matrix1, rows1);
            free_matrix(matrix2, rows2);
            free_matrix(result, rows1);
            break;

        case 3:  // Transpose
            if (scanf("%d %d", &rows1, &cols1) != 2 || rows1 <= 0 || cols1 <= 0) {
                printf("n/a");
                return 0;
            }

            matrix1 = (int **)malloc(rows1 * sizeof(int *));
            result = (int **)malloc(cols1 * sizeof(int *));
            if (matrix1 == NULL || result == NULL) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, cols1);
                return 0;
            }

            if (!input(matrix1, &rows1, &cols1)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, cols1);
                return 0;
            }

            if (!transpose(matrix1, rows1, cols1, result)) {
                printf("n/a");
                free_matrix(matrix1, rows1);
                free_matrix(result, cols1);
                return 0;
            }

            output(result, cols1, rows1);
            free_matrix(matrix1, rows1);
            free_matrix(result, cols1);
            break;
    }

    return 0;
}

int input(int **matrix, int *n, int *m) {
    for (int i = 0; i < *n; i++) {
        int s = *m;
        matrix[i] = (int *)malloc(s * sizeof(int));
        if (matrix[i] == NULL) {
            return 0;
        }
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                for (int k = 0; k < i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return 0;
            }
        }
    }
    return 1;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j != m - 1) printf(" ");
        }
        if (i != n - 1) printf("\n");
    }
}

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (n_first != n_second || m_first != m_second) return 0;
    *n_result = n_first;
    *m_result = m_first;
    for (int i = 0; i < n_first; i++) {
        matrix_result[i] = (int *)malloc(*m_result * sizeof(int));
        if (matrix_result[i] == NULL) {
            return 0;
        }

        for (int j = 0; j < m_first; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return 1;
}

int transpose(int **matrix, int n, int m, int **matrix_result) {
    for (int i = 0; i < n; i++) {
        matrix_result[i] = (int *)malloc(m * sizeof(int));
        if (matrix_result[i] == NULL) {
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix_result[j][i] = matrix[i][j];
        }
    }
    return 1;
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    *n_result = n_first;
    *m_result = m_second;
    if (n_second != m_first) return 0;

    for (int i = 0; i < n_first; i++) {
        matrix_result[i] = (int *)malloc(*m_result * sizeof(int));
        if (matrix_result[i] == NULL) {
            return 0;
        }
        for (int j = 0; j < m_second; j++) {
            matrix_result[i][j] = 0;
            for (int k = 0; k < m_first; k++) {
                matrix_result[i][j] += matrix_first[i][k] * matrix_second[k][j];
            }
        }
    }
    return 1;
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
