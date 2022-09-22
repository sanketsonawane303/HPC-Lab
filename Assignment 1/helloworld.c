#include <omp.h>
#include <stdio.h>

int main() {
  int threadCount;

  printf("Enter number of threads: ");
  scanf("%d", &threadCount);
  omp_set_num_threads(threadCount);

#pragma omp parallel
  {
    int id = omp_get_thread_num();

    printf("Hello(%d) ", id);
    printf("World(%d)\n", id);
  }

  return 0;
}
