#include <stdio.h>

void initWith(float num, float *a, int SIZE)
{
  for(int i = 0; i < SIZE; ++i)
  {
    a[i] = num;
  }
}

__global__
void matrixMultiply(float *result, float *a, float *b, int N, int SIZE)
{
  int start = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = gridDim.x * blockDim.x;

  for(int i = start; i < SIZE; i += stride)
  {
    int row = i / N;

    float sum = 0;

    for (int j = 0; j < N; j++)
    {
      sum += a[row * N + j] * b[N * j + row];
    }

    result[i] = sum;
  }
}

void checkElementsAre(float target, float *array, int SIZE)
{
  for(int i = 0; i < SIZE; i++)
  {
    if(array[i] != target)
    {
      printf("FAIL: array[%d] - %0.0f does not equal %0.0f\n", i, array[i], target);
      exit(1);
    }
  }
  printf("SUCCESS! All values multiplied correctly.\n");
}

int main()
{
  const int N = 1024;
  const int SIZE = N * N; // sqaure matrix
  size_t size = SIZE * sizeof(float);

  float *a;
  float *b;
  float *c;

  cudaMallocManaged(&a, size);
  cudaMallocManaged(&b, size);
  cudaMallocManaged(&c, size);

  initWith(3, a, SIZE);
  initWith(4, b, SIZE);
  initWith(0, c, SIZE);

  matrixMultiply<<<100, 1024>>>(c, a, b, N, SIZE);
  cudaDeviceSynchronize();

  checkElementsAre(12288, c, SIZE);

  cudaFree(a);
  cudaFree(b);
  cudaFree(c);
}
