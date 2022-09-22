#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000000

void sequential(int A[], int k, int C[]) {
  int i;
  double start, end, duration;

  start = omp_get_wtime();

  for (i = 0; i < N; i++)
    C[i] = A[i] + k;

  end = omp_get_wtime();
  duration = end - start;

  printf("---Sequential---\n");
  printf("Time taken: %lf\n\n", duration);
}

void parallel(int threads, int A[], int k, int C[]) {
  int i;
  double start, end, duration;

  omp_set_num_threads(threads);

  start = omp_get_wtime();

#pragma omp parallel for private(k)
  for (i = 0; i < N; i++)
    C[i] = A[i] + k;

  end = omp_get_wtime();
  duration = end - start;

  printf("---Parallel (%d threads)---\n", threads);
  printf("Time taken: %lf\n\n", duration);
}

int main() {
  int* A = (int*)malloc(N * sizeof(int));
  int* C = (int*)malloc(N * sizeof(int));

  int i, temp = 0, k = 100;
  for (i = 0; i < N; i++) {
    A[i] = temp;
    temp = (temp + 1) % 100;
  }

  sequential(A, k, C);
  parallel(1, A, k, C);
  parallel(2, A, k, C);
  parallel(3, A, k, C);
  parallel(4, A, k, C);

  free(A);
  free(C);

  return 0;
}
