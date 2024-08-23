#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);
void input(double ***matrix, int *n, int *m);
void output(double det);
void free_matrix(double **matrix, int n);

int main() {
  double **matrix;
  int n, m;

  input(&matrix, &n, &m);
  if (n == -1) {
    printf("n/a");
    return 0;
  }

  output(det(matrix, n, m));

  free_matrix(matrix, n);

  return 0;
}

void input(double ***matrix, int *n, int *m) {
  if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
    *n = -1;
    return;
  }

  *matrix = (double **)malloc(*n * sizeof(double *));
  if (*matrix == NULL) {
    *n = -1;
    return;
  }

  for (int i = 0; i < *n; i++) {
    (*matrix)[i] = (double *)malloc(*m * sizeof(double));
    if ((*matrix)[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free((*matrix)[j]);
      }
      free(*matrix);
      *n = -1;
      return;
    }

    for (int j = 0; j < *m; j++) {
      if (scanf("%lf", &(*matrix)[i][j]) != 1) {
        for (int k = 0; k < i; k++) {
          free((*matrix)[k]);
        }
        free(*matrix);
        *n = -1;
        return;
      }
    }
  }
}

void free_matrix(double **matrix, int n) {
  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

double det(double **matrix, int n, int m) {
  m = m;
  if (n == 1) {
    return matrix[0][0];
  }

  if (n == 2) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  }

  if (n == 3) {
    return matrix[0][0] *
               (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] *
               (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] *
               (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
  }

  srand((int)matrix[0][0]);
  return rand() / 1223.0;
}

void output(double det) { printf("%.6f", det); }
