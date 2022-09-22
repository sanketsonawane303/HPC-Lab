// C Program to find the minimum scalar product of two vectors (dot product)
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
}

void sort_des(int arr[], int n) {
  int i, j;
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (arr[i] < arr[j]) {
        int a = arr[i];
        arr[i] = arr[j];
        arr[j] = a;
      }
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

  double start, end, duration;
  start = omp_get_wtime();

  sort(arr1, n);
  sort_des(arr2, n);
  int sum = 0;
  for (i = 0; i < n; i++) {
    sum = sum + (arr1[i] * arr2[i]);
  }

  end = omp_get_wtime();
  duration = end - start;

  printf("Sum: %d\n", sum);
  printf("Time taken: %lf", duration);

  return 0;
}
