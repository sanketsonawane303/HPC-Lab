#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200

void parallelStatic(int chunks, int A[], int k, int C[]) {
  int i;
  double start, end, duration;

  start = omp_get_wtime();

#pragma omp parallel for schedule(static, chunks)
  for (i = 0; i < N; i++)
    C[i] = A[i] + k;

  end = omp_get_wtime();
  duration = end - start;

  printf("---Static (%d chunks)---\n", chunks);
  printf("Time taken: %15.15lf\n\n", duration);
}

void parallelDynamic(int chunks, int A[], int k, int C[]) {
  int i;
  double start, end, duration;

  start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic, chunks)
  for (i = 0; i < N; i++)
    C[i] = A[i] + k;

  end = omp_get_wtime();
  duration = end - start;

  printf("---Dynamic (%d chunks)---\n", chunks);
  printf("Time taken: %15.15lf\n\n", duration);
}

int main() {
  int* A = (int*)malloc(N * sizeof(int));
  int* C = (int*)malloc(N * sizeof(int));

  int i, temp = 0, k = 100;
  for (i = 0; i < N; i++) {
    A[i] = temp;
    temp = (temp + 1) % 100;
  }

  parallelStatic(2, A, k, C);
  parallelStatic(5, A, k, C);
  parallelStatic(10, A, k, C);
  parallelStatic(20, A, k, C);

  parallelDynamic(2, A, k, C);
  parallelDynamic(5, A, k, C);
  parallelDynamic(10, A, k, C);
  parallelDynamic(20, A, k, C);

  free(A);
  free(C);

  return 0;
}
