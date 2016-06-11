#include <iostream>
#include <assert.h>
#include <algorithm>
#include <array>
#include <cstdio>

typedef enum { RED, WHITE, BLUE } Color;

void swap(int& i, int& j)
{
  int tmp = i;
  i = j;
  j = tmp;
}

int getMed(int x, int y, int z)
{
  if (x < y) {
    if (y < z) {
      return y;
    }
    else if (x < z) {
      return z;
    }
    return x;
  }
  else if (x < z) {
    return x;
  }
  else if (y < z) {
    return z;
  }
  return y;
}

template<std::size_t SIZE>
void printArray(std::array<int, SIZE>& A, const char* msg=0)
{
  if (msg) {
    std::cout << msg << ": ";
  }
  for (auto& e : A) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

template<std::size_t SIZE>
void doDutchFlagPartition(std::array<int, SIZE>& A, int pivot_index)
{
  int pivot_value = A[pivot_index];

  printf("pivot_index=%d, pivot_value = %d\n", pivot_index, pivot_value);

  for (int i = 0; i < A.size(); ++i)
    for (int j = i + 1; j < A.size(); ++j)
      if (A[j] < pivot_value) {
        swap(A[i], A[j]);
        break; // break j-loop
      }

  // now the values smaller than pivot_value are gathered in left-hand of array

  for (int i = A.size() - 1; i >= 0 && A[i] >= pivot_value; --i)
    for (int j = i - 1; j >= 0 && A[j] >= pivot_value; --j)
      if (A[j] > pivot_value) {
        swap(A[i], A[j]);
        break; // break j-loop
      }
}

template<std::size_t SIZE>
void doDutchFlagPartition2(std::array<int, SIZE>& A, int pivot_index)
{
  int pivot_value = A[pivot_index];

  printf("pivot_index=%d, pivot_value = %d\n", pivot_index, pivot_value);

  int smaller = 0;
  for (int i = smaller; i < A.size(); ++i)
    if (A[i] < pivot_value) {
      swap(A[i], A[smaller++]);
    }

  // now the values smaller than pivot_value are gathered in left-hand of array

  int larger = A.size() - 1;
  for (int i = larger; i >= 0 && A[i] >= pivot_value; --i)
    if (A[i] > pivot_value) {
      swap(A[i], A[larger--]);
    }
}

template<std::size_t SIZE>
void StdSort(std::array<int, SIZE>& A)
{
  std::cout << "applying " << __func__ << std::endl;
  printArray(A, "before");
  std::sort(A.begin(), A.end());
  printArray(A, "after ");
  std::cout << std::endl;
}

template<std::size_t SIZE>
void DutchFlagPartition(std::array<int, SIZE>& A)
{
  std::cout << "applying " << __func__ << std::endl;
  printArray(A, "before");
  int i = 0;
  while (A[i] != WHITE && i < A.size()) {
    ++i;
  }
  doDutchFlagPartition(A, i);
  printArray(A, "after ");
  std::cout << std::endl;
}

template<std::size_t SIZE>
void DutchFlagPartition2(std::array<int, SIZE>& A)
{
  std::cout << "applying " << __func__ << std::endl;
  printArray(A, "before");
  int i = 0;
  while (A[i] != WHITE && i < A.size()) {
    ++i;
  }
  doDutchFlagPartition2(A, i);
  printArray(A, "after ");
  std::cout << std::endl;
}



int main(int argc, char* argv[])
{
  std::array<int, 20> T;
  for (auto& e : T) {
    e = rand() % 3;
  }

  std::array<int, T.size()> A = T, B = T, C = T;

  StdSort(A);
  DutchFlagPartition(B);
  DutchFlagPartition2(C);

  assert(A == B);
  std::cout << "Success. The results of StdSort and DutchFlagPartition are same." << std::endl;

  assert(A == C);
  std::cout << "Success. The results of StdSort and DutchFlagPartition2 are same." << std::endl;

  return 0;
}
