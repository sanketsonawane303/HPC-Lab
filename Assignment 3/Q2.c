#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void add(int threads, int** A, int** B, int** C, int n) {
  int i, j;
  double start, end, duration;

  omp_set_num_threads(threads);

  start = omp_get_wtime();

#pragma omp parallel for private(j)
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      C[i][j] = A[i][j] + B[i][j];

  end = omp_get_wtime();
  duration = end - start;

  printf("---%d threads -  %d size---\n", threads, n);

  // for (i = 0; i < n; i++) {
  //   for (j = 0; j < n; j++)
  //     printf("%d ", C[i][j]);
  //   printf("\n");
  // }

  printf("Time taken: %lf\n\n", duration);
}

int main() {
  int i, j, n, temp = 0;
  scanf("%d", &n);

  int** A = (int**)malloc(n * sizeof(int*));
  int** B = (int**)malloc(n * sizeof(int*));
  int** C = (int**)malloc(n * sizeof(int*));

  for (i = 0; i < n; i++) {
    A[i] = (int*)malloc(n * sizeof(int));
    B[i] = (int*)malloc(n * sizeof(int));
    C[i] = (int*)malloc(n * sizeof(int));
  }

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      A[i][j] = temp;
      B[i][j] = temp;

      temp = (temp + 1) % 100;
    }

  add(1, A, B, C, n);
  add(2, A, B, C, n);
  add(4, A, B, C, n);
  add(8, A, B, C, n);

  for (i = 0; i < n; i++) {
    free(A[i]);
    free(B[i]);
    free(C[i]);
  }

  free(A);
  free(B);
  free(C);

  return 0;
}
