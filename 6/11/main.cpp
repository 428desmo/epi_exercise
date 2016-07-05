#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>

#include <vector>
#include <random>

void ShowArray(std::vector<int>& A);

void GetRandomSubset(std::vector<int>* A_ptr, int size)
{
  std::vector<int>& A = *A_ptr;
  srand(time(NULL));

  for (int i = 0; i < size; ++i) {
    int j = (rand() % (A.size() - i)) + i;
    printf("[%d] chosen index = %d (value = %d)\n", i, j, A[j]);
    printf("swap %d and %d\n", A[i], A[j]);
    std::swap(A[i], A[j]);
  }
}

void GetRandomSubset2(std::vector<int>* A_ptr, int size)
{
  std::vector<int>& A = *A_ptr;
  std::default_random_engine seed((std::random_device())());

  for (int i = 0; i < size; ++i) {
    int j = std::uniform_int_distribution<int>{i, static_cast<int>(A.size()) - 1}(seed);
    printf("[%d] chosen index = %d (value = %d)\n", i, j, A[j]);
    printf("swap %d and %d\n", A[i], A[j]);
    std::swap(A[i], A[j]);
  }
}

void ShowArray(std::vector<int>& A)
{
  for (int i = 0; i < 10; ++i) {
    printf("%d ", A[i]);
  }
  printf("\n");
}

int main(int argc, char* argv[])
{
  std::vector<int> A = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  ShowArray(A);
  GetRandomSubset(&A, 5);
  ShowArray(A);
  GetRandomSubset(&A, 5);
  ShowArray(A);
  GetRandomSubset(&A, 5);
  ShowArray(A);

  GetRandomSubset2(&A, 5);
  ShowArray(A);
  GetRandomSubset2(&A, 5);
  ShowArray(A);
  GetRandomSubset2(&A, 5);
  ShowArray(A);

  return 0;
}
