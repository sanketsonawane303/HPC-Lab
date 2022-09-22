// C Program to find the minimum scalar product of two vectors (dot product)
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
  int c = *a;
  *a = *b;
  *b = c;
}

void parallelSort(int arr[], int n) {
  int i, j;

  for (i = 0; i < n; i++) {
#pragma omp for
    for (j = i % 2; j < n - 1; j += 2) {
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
    }
  }
}

void parallelSortDes(int arr[], int n) {
  int i, j;

  for (i = 0; i < n; i++) {
#pragma omp for
    for (j = i % 2; j < n - 1; j += 2) {
      if (arr[j] < arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
    }
  }
}

int main() {
  // fill the code;
  int i, n = 100000;
  int* arr1 = (int*)malloc(n * sizeof(int));
  int* arr2 = (int*)malloc(n * sizeof(int));

  int temp = 0;
  for (i = 0; i < n; i++) {
    arr1[i] = temp;
    arr2[i] = temp * 2;

    temp = (temp + 1) % 100;
  }

  int sum = 0;

  omp_set_num_threads(4);

  double start, end, duration;
  start = omp_get_wtime();

#pragma omp parallel
  {
    parallelSort(arr1, n);
    parallelSortDes(arr2, n);

#pragma omp for reduction(+ : sum)
    for (i = 0; i < n; i++) {
      sum = sum + (arr1[i] * arr2[i]);
    }
  }

  end = omp_get_wtime();
  duration = end - start;

  printf("Sum: %d\n", sum);
  printf("Time taken: %lf", duration);
  return 0;
}
