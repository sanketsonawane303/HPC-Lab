#include <omp.h>
#include <stdio.h>

void sequential(int);
void SPMD(int, int);
void worksharing(int, int);

int main() {
  int n;
  printf("Enter n (sum of squares from 1 to n): ");
  scanf("%d", &n);

  sequential(n);

  SPMD(1, n);
  SPMD(2, n);
  SPMD(3, n);
  SPMD(4, n);

  worksharing(1, n);
  worksharing(2, n);
  worksharing(3, n);
  worksharing(4, n);

  return 0;
}

void sequential(int n) {
  long long i, sum = 0;
  double start, end, duration;

  start = omp_get_wtime();

  for (i = 1; i <= n; i++)
    sum += i * i;

  end = omp_get_wtime();
  duration = end - start;

  printf("---Sequential---\n");
  printf("Sum of squares: %lld\n", sum);
  printf("Time taken: %lf\n\n", duration);
}

void SPMD(int threads, int n) {
  // assuming all requested threads are granted

  long long sum = 0;
  double start, end, duration;

  omp_set_num_threads(threads);

  start = omp_get_wtime();

#pragma omp parallel
  {
    long long i;
    int id = omp_get_thread_num();
    long long s = 0;

    for (i = id + 1; i <= n; i += threads)
      s += i * i;

#pragma omp critical
    sum += s;
  }

  end = omp_get_wtime();
  duration = end - start;

  printf("---SPMD with %d threads---\n", threads);
  printf("Sum of squares: %lld\n", sum);
  printf("Time taken: %lf\n\n", duration);
}

void worksharing(int threads, int n) {
  long long i, sum = 0;
  double start, end, duration;

  omp_set_num_threads(threads);

  start = omp_get_wtime();

#pragma omp parallel for reduction(+ : sum)
  for (i = 1; i <= n; i++)
    sum += i * i;

  end = omp_get_wtime();
  duration = end - start;

  printf("---Worksharing with %d threads---\n", threads);
  printf("Sum of squares: %lld\n", sum);
  printf("Time taken: %lf\n\n", duration);
}
