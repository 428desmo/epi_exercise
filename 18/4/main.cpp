#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <vector>

bool HasTwoSum(std::vector<int>& V, int n)
{
  int i = 0, j = V.size() - 1;
  while (i <= j) {
    if (V[i] + V[j] == n)
      return true;
    else if (V[i] + V[j] > n)
      --j;
    else
      ++i;
  }
  return false;
}

bool HasThreeSum(std::vector<int>& V, int n)
{
  std::sort(V.begin(), V.end());

  for (int i = 0; i < V.size(); ++i) {
    if (HasTwoSum(V, n - V[i]))
      return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  std::vector<int> A = {11, 2, 5, 7, 3};

  assert(HasThreeSum(A, 21));
  assert(!HasThreeSum(A, 22));

  return 0;
}
