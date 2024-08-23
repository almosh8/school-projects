#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);
void input(int ***matrix, int *n, int *m);
void output(int **matrix, int n, int m);
void free_matrix(int **matrix, int n);

int main() {
  int **matrix, **result;
  int n, m;

  input(&matrix, &n, &m);
  if (n == -1) {
    printf("n/a");
    return 0;
  }

  result = (int **)malloc(n * sizeof(int *));
  if (result == NULL) {
    printf("n/a");
    free_matrix(matrix, n);
    return 0;
  }

  for (int i = 0; i < n; i++) {
    result[i] = (int *)malloc(m * sizeof(int));
    if (result[i] == NULL) {
      printf("n/a");
      free_matrix(matrix, n);
      free_matrix(result, i);
      return 0;
    }
  }

  sort_vertical(matrix, n, m, result);
  output(result, n, m);
  printf("\n\n");

  sort_horizontal(matrix, n, m, result);
  output(result, n, m);

  free_matrix(matrix, n);
  free_matrix(result, n);

  return 0;
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
  int *array = (int *)malloc(n * m * sizeof(int *));

  int x = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      array[x] = matrix[i][j];
      x++;
    }
  }

  x = 0;
  for (int i = 0; i < m; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < n; j++) {
        result_matrix[j][i] = array[x];
        x++;
      }
    } else {
      for (int j = n - 1; j >= 0; j--) {
        result_matrix[j][i] = array[x];
        x++;
      }
    }
  }
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
  int *array = (int *)malloc(n * m * sizeof(int *));

  int x = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      array[x] = matrix[i][j];
      x++;
    }
  }

  x = 0;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < m; j++) {
        result_matrix[i][j] = array[x];
        x++;
      }
    } else {
      for (int j = m - 1; j >= 0; j--) {
        result_matrix[i][j] = array[x];
        x++;
      }
    }
  }
}

void input(int ***matrix, int *n, int *m) {
  if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
    *n = -1;
    return;
  }

  *matrix = (int **)malloc(*n * sizeof(int *));
  if (*matrix == NULL) {
    *n = -1;
    return;
  }

  for (int i = 0; i < *n; i++) {
    (*matrix)[i] = (int *)malloc(*m * sizeof(int));
    if ((*matrix)[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free((*matrix)[j]);
      }
      free(*matrix);
      *n = -1;
      return;
    }

    for (int j = 0; j < *m; j++) {
      if (scanf("%d", &(*matrix)[i][j]) != 1) {
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

void output(int **matrix, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", matrix[i][j]);
      if (j < m - 1)
        printf(" ");
    }
    if (i < n - 1)
      printf("\n");
  }
}

void free_matrix(int **matrix, int n) {
  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
