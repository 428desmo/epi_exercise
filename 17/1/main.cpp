#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <vector>

int CalcScorePatterns(int total_score, std::vector<int>& scores)
{
  std::vector<int> patterns;
  patterns.reserve(total_score + 1);
  for (int i = 0; i <= total_score; ++i) {
    patterns[i] = 0;
  }
  patterns[0] = 1;

  for (int s : scores) {
    for (int i = s; i <= total_score; ++i) {
//      printf("%d: (%d)%d + (%d)%d -> %d\n", s, i, patterns[i], i-s, patterns[i - s], patterns[i] + patterns[i - s]);
      patterns[i] += patterns[i - s];
    }
  }

  std::cout << "There are " << patterns[total_score] << " pattern to construct " << total_score << " from { ";
  for (int s : scores) {
    std::cout << s << " ";
  }
  std::cout << "}." << std::endl;

  return patterns[total_score];
}

int main(int argc, char* argv[])
{
  std::vector<int> V1 = {2, 3, 7};
  CalcScorePatterns(12, V1);

  std::vector<int> V2 = {1,5,10};
  CalcScorePatterns(20, V2);

  return 0;
}
