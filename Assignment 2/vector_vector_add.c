#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000000

void sequential(int A[], int B[], int C[]) {
  int i;
  double start, end, duration;

  start = omp_get_wtime();

  for (i = 0; i < N; i++)
    C[i] = A[i] + B[i];

  end = omp_get_wtime();
  duration = end - start;

  printf("---Sequential---\n");
  printf("Time taken: %lf\n\n", duration);
}

void parallel(int threads, int A[], int B[], int C[]) {
  int i;
  double start, end, duration;

  omp_set_num_threads(threads);

  start = omp_get_wtime();

#pragma omp parallel for
  for (i = 0; i < N; i++)
    C[i] = A[i] + B[i];

  end = omp_get_wtime();
  duration = end - start;

  printf("---Parallel (%d threads)---\n", threads);
  printf("Time taken: %lf\n\n", duration);
}

int main() {
  int* A = (int*)malloc(N * sizeof(int));
  int* B = (int*)malloc(N * sizeof(int));
  int* C = (int*)malloc(N * sizeof(int));

  int i, temp = 0;
  for (i = 0; i < N; i++) {
    A[i] = temp;
    B[i] = temp * 2;

    temp = (temp + 1) % 100;
  }

  sequential(A, B, C);
  parallel(1, A, B, C);
  parallel(2, A, B, C);
  parallel(3, A, B, C);
  parallel(4, A, B, C);

  free(A);
  free(B);
  free(C);

  return 0;
}
