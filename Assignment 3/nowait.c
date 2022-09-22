#include <omp.h>
#include <stdio.h>

void withoutNowait() {
  int i;

#pragma omp parallel
  {
#pragma omp for
    for (i = 0; i < 4; i++)
      printf("Inner (%d)\n", omp_get_thread_num());

    printf("Outer (%d)\n", omp_get_thread_num());
  }
}

void withNowait() {
  int i;

#pragma omp parallel
  {
#pragma omp for nowait
    for (i = 0; i < 4; i++)
      printf("Inner (%d)\n", omp_get_thread_num());

    printf("Outer (%d)\n", omp_get_thread_num());
  }
}

int main() {
  printf("Without nowait ------\n");
  withoutNowait();

  printf("\n\n\nWith nowait --------\n");
  withNowait();

  return 0;
}
