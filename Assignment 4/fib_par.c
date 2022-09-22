#include <omp.h>
#include <stdio.h>

int fib(int n, int dp[]) {
  int x, y;

  if (n < 2)
    return n;

  if (dp[n] != 0)
    return dp[n];

#pragma omp task shared(x, dp)
  x = fib(n - 1, dp);

#pragma omp task shared(y, dp)
  y = fib(n - 2, dp);

#pragma omp taskwait
  return dp[n] = x + y;
}

int main() {
  int n = 20, f;
  double start, end, duration;

  int dp[n + 1];
  for (int i = 0; i <= n; i++)
    dp[i] = 0;

  omp_set_num_threads(4);

  start = omp_get_wtime();

#pragma omp parallel
#pragma omp single
  f = fib(n, dp);

  end = omp_get_wtime();
  duration = end - start;

  printf("fib(%d) = %d\n\n", n, f);
  printf("Time taken: %lf %15.15lf", duration, duration);

  return 0;
}
