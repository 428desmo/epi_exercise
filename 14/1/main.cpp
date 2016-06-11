#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <vector>


using std::vector;

vector<int> InterSection(const vector<int>& V1, const vector<int>& V2)
{
  vector<int> V;
  auto e1 = V1.begin();
  auto e2 = V2.begin();
  while (e1 != V1.end() && e2 != V2.end()) {
    if (*e1 == *e2) {
      V.emplace_back(*e1);
      while (*e1 == *e2)
        ++e1;
    }
    else if (*e1 < *e2) {
      ++e1;
    }
    else {
      ++e2;
    }
  }
  return V;
}

vector<int> InterSection2(const vector<int>& A, const vector<int>& B)
{
  vector<int> V;
  for (int i = 0; i < A.size(); ++i) {
    if ((i == 0 || A[i] != A[i - 1]) &&
       std::binary_search(B.begin(), B.end(), A[i]))
    {
      V.emplace_back(A[i]);
    }
  }
  return V;
}

void DebugPrint(const vector<int>& V)
{
  for (auto& e : V) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[])
{
  vector<int> V1 = {2, 3, 3, 5, 5, 6, 7, 7, 8, 12};
  vector<int> V2 = {5, 5, 6, 8, 8, 9, 10, 10};

  vector<int> V = InterSection(V1, V2);
  DebugPrint(V);

  V = InterSection2(V1, V2);
  DebugPrint(V);

  return 0;
}
