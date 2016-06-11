#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

struct IteratorCurrAndEnd {
  bool operator>(const IteratorCurrAndEnd& rhs) const {
    return *current > *rhs.current;
  }

  std::vector<int>::const_iterator current;
  std::vector<int>::const_iterator end;
};


std::vector<int> MergeSortedArrays(const std::vector<std::vector<int>>& sorted_arrays)
{
  std::priority_queue<IteratorCurrAndEnd, std::vector<IteratorCurrAndEnd>, std::greater<IteratorCurrAndEnd>> min_heap;

  // putting the pair of iterators into the priority_queue
  // it is sorted by the first one (i.e. cbegin() of each sorted_array)
  for (const std::vector<int>& sorted_array : sorted_arrays) {
    min_heap.emplace(IteratorCurrAndEnd{sorted_array.cbegin(), sorted_array.cend()});
  }

  std::vector<int> result;
  while (!min_heap.empty()) {
    // get the sorted_array which has smallest one as .current
    auto smallest_array = min_heap.top();
    min_heap.pop();
    if (smallest_array.current != smallest_array.end) {
      // if current == end, it means iterator reaches sorted_array.cend()
      // so we have assured that current is pointing the valid element
      result.emplace_back(*smallest_array.current);

      //  move the iterator to the next, and put the new pair of iterators into min_heap
      min_heap.emplace(IteratorCurrAndEnd{std::next(smallest_array.current), smallest_array.end});
    }
  }
  return result;
}
  
int main(int argc, char* argv[])
{
  std::vector<int> A = {3, 5, 7};
  std::vector<int> B = {0, 6};
  std::vector<int> C = {0, 6, 28};

  std::vector<std::vector<int>> Arrays = {A, B, C};

  std::vector<int> Result = MergeSortedArrays(Arrays);
  std::vector<int> Expected = {0, 0, 3, 5, 6, 6, 7, 28};

  assert(Result == Expected);
  std::cout << "success" << std::endl;

  return 0;
}
