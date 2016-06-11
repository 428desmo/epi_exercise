#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#include <climits>

template<size_t SIZE>
int BuyAndSellStockOnce_BF(const std::array<int, SIZE>& A)
{
  int max = 0;
  int if_count = 0;
  for (int i = 0; i < A.size(); ++i)
    for (int j = i; j < A.size(); ++j)
{
++if_count;
      if (A[j] - A[i] > max)
        max = A[j] - A[i];
}
std::cout << __func__ << " if_count = " << if_count << std::endl;

  return max;
}

int highest(int x, int y, int z)
{
/*
  if (x < y) {
    if (y < z)
      return z;
    return y;
  }
  else if (x < z)
    return z;
  return x;
*/
  return std::max(x, std::max(y, z));
}

int g_count = 0;

template<size_t SIZE>
int doBuyAndSellStockOnce_DivConq(const std::array<int, SIZE>& A, int l, int r, int& min, int& max)
{
  if (l == r) {
    g_count++;
    min = max = A[l];
    return 0;
  }
  int Lmaxprof,Rmaxprof,Lmin,Lmax,Rmin,Rmax;
  Lmaxprof = doBuyAndSellStockOnce_DivConq(A, l, l + (r - l)/2, Lmin, Lmax);
  Rmaxprof = doBuyAndSellStockOnce_DivConq(A, l + (r - l)/2 + 1, r, Rmin, Rmax);
  min = std::min(Lmin, Rmin);
  max = std::max(Lmax, Rmax);
  int maxprof = highest(Lmaxprof, Rmaxprof, Rmax - Lmin);
//  printf("A[%d]=%d, A[%d]=%d, min = %d, max = %d, maxprof = %d\n", l, A[l], r, A[r], min, max, maxprof);
  return maxprof;

}

template<size_t SIZE>
int BuyAndSellStockOnce_2(const std::array<int, SIZE>& A)
{
  int min, max;
  int maxprof = doBuyAndSellStockOnce_DivConq(A, 0, A.size() - 1, min, max);
  printf("maxprof = %d, min = %d, max = %d, count = %d\n", maxprof, min, max, g_count);
  return maxprof;
}

template<size_t SIZE>
int BuyAndSellStockOnce_3(const std::array<int, SIZE>& A)
{
  int minSoFar = std::numeric_limits<int>::max();
  int maxProfit = 0;

  for (auto& e : A) {
    int maxProfitToday = e - minSoFar;
    minSoFar = std::min(minSoFar, e);
    maxProfit = std::max(maxProfit, maxProfitToday);
  }
  printf("maxprof = %d, count = %lu\n", maxProfit, A.size());
  return maxProfit;
}


int main(int argc, char* argv[])
{
#if 1
  std::array<int, 10> A = {310, 315 ,275, 295, 260, 270, 290, 230, 255, 250};
#else
  std::array<int, 50000> A;
  int t = 500;
  for (auto& e : A) {
    t += (rand() % 101) - 50; //-50 ~ +50
    if (t < 0)
      t = 0;
    if (t > 1000)
      t = 1000;
    e = t;
  }
#endif

  int r1 = BuyAndSellStockOnce_BF(A);
  int r2 = BuyAndSellStockOnce_2(A);
  int r3 = BuyAndSellStockOnce_3(A);
  assert(r1 == r2);
  assert(r1 == r3);

  std::cout << "Success." << std::endl;

  return 0;
}
