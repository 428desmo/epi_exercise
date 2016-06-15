#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <stack>

std::stack<int> A, B, C;

void Dump(const char* msg, int n)
{
  std::cout << msg << " " << n << std::endl;

  std::stack<int> X = A;
  std::stack<int> Y;
  std::cout << "A: ";
  while (!X.empty()) {
    Y.emplace(X.top());
    X.pop();
  }
  while (!Y.empty()) {
    std::cout << Y.top() << " ";
    Y.pop();
  }
  std::cout << std::endl;

  X = B;
  std::cout << "B: ";
  while (!X.empty()) {
    Y.emplace(X.top());
    X.pop();
  }
  while (!Y.empty()) {
    std::cout << Y.top() << " ";
    Y.pop();
  }
  std::cout << std::endl;

  X = C;
  std::cout << "C: ";
  while (!X.empty()) {
    Y.emplace(X.top());
    X.pop();
  }
  while (!Y.empty()) {
    std::cout << Y.top() << " ";
    Y.pop();
  }
  std::cout << "\n" << std::endl;
}

void HanoiTowerMoveN(int n, std::stack<int>& from, std::stack<int>& to, std::stack<int>& tmp)
{
  assert(n >= 1);
  if (n  == 1) {
    if (to.empty() || to.top() > from.top()) {
      to.emplace(from.top());
      from.pop();
    }
  }
  else {
    HanoiTowerMoveN(n - 1, from, tmp, to);
    Dump("(a)", n - 1);
    HanoiTowerMoveN(1, from, to, tmp);
    Dump("(b)", 1);
    HanoiTowerMoveN(n - 1, tmp, to, from);
    Dump("(c)", n - 1);
  }
}

int main(int argc, char* argv[])
{
  for (int i = 10; i > 0; --i) {
    A.emplace(i);
  }
  Dump("init", 0);

  HanoiTowerMoveN(A.size(), A, B, C);

  return 0;
}
