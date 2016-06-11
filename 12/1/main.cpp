#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <vector>

int SimpleBinSearch(std::vector<int>&sorted, int target)
{
  int left = 0, right = sorted.size() - 1;
  while (left <= right) {
    int cur = left + (right - left)/2;
    if (sorted[cur] ==  target)
      return cur;
    else if (sorted[cur] < target)
      left = cur + 1;
    else
      right = cur - 1;
  }
  return -1; 
}


struct Student {
  std::string name;
  double GPA;
};

const static bool comp_func(const Student& lhs, const Student& rhs) {
  if (lhs.GPA != rhs.GPA)
    return lhs.GPA > rhs.GPA;
  return lhs.name < rhs.name;
}

bool SearchStudent(const std::vector<Student>& students, const Student& target) {
  return std::binary_search(students.begin(), students.end(), target, comp_func);
}

const static std::function<bool(const Student&, const Student&)> comp_func_lamda =
  [](const Student& lhs, const Student& rhs) -> bool
{
  if (lhs.GPA != rhs.GPA)
    return lhs.GPA > rhs.GPA;
  return lhs.name < rhs.name;
};

bool SearchStudent(const std::vector<Student>& students, const Student& target,
                   const std::function<bool(const Student&, const Student&)>& func) {
  return std::binary_search(students.begin(), students.end(), target, func);
}


int FirstOccurence(std::vector<int>&sorted, int target)
{
  int found = SimpleBinSearch(sorted, target);
  int first = -1;
  while ((found >= 0) && (sorted[found] == target)) {
    first = found;
    --found;
  }
  return first;
}

int FirstOccurence2(std::vector<int>&sorted, int target)
{
  int left = 0, right = sorted.size() - 1, result = -1;
  while (left <= right) {
    int cur = left + (right - left)/2;
    if (sorted[cur] ==  target) {
      result = cur; // provisional
      right = cur - 1; // search more left
    }
    else if (sorted[cur] < target)
      left = cur + 1;
    else
      right = cur - 1;
  }
  return result;
}


int main(int argc, char* argv[])
{
  // testing SimpleBinSearch
  std::vector<int> A;
  for (int j = 1; j < 100; ++j) {
    A.clear();
    for (int i = 0; i < j; ++i)
      A.emplace_back(i);

    for (int i = 0; i < j; ++i) 
      assert(SimpleBinSearch(A, i) == i);
  }
  std::cout << "SimpleBinSearch test success" << std::endl;

  // testing SearchStudent
  std::vector<Student> B = {{"Alice", 4.00}, {"Bob", 3.75}, {"Carol", 3.75}, {"Darren", 3.5}};
  assert(SearchStudent(B, {"Alice", 4.00}) == true);
  assert(SearchStudent(B, {"Bob", 3.75}) == true);
  assert(SearchStudent(B, {"Carol", 3.75}) == true);
  assert(SearchStudent(B, {"Darren", 3.5}) == true);
  assert(SearchStudent(B, {"Dylan", 3.75}) == false);
  std::cout << "SearchStudent test success" << std::endl;

  // testing SearchStudent-lamda
  assert(SearchStudent(B, {"Alice", 4.00}, comp_func_lamda) == true);
  assert(SearchStudent(B, {"Bob", 3.75}, comp_func_lamda) == true);
  assert(SearchStudent(B, {"Carol", 3.75}, comp_func_lamda) == true);
  assert(SearchStudent(B, {"Darren", 3.5}, comp_func_lamda) == true);
  assert(SearchStudent(B, {"Dylan", 3.75}, comp_func_lamda) == false);
  std::cout << "SearchStudent-lamda test success" << std::endl;

  // testing FirstOccurence
  std::vector<int> C = {-14, -10, 2, 108, 108, 243, 243, 285, 285, 285, 401};
  assert(FirstOccurence(C, -20) == -1);
  assert(FirstOccurence(C,   0) == -1);
  assert(FirstOccurence(C, 500) == -1);
  assert(FirstOccurence(C, -14) ==  0);
  assert(FirstOccurence(C, -10) ==  1);
  assert(FirstOccurence(C,   2) ==  2);
  assert(FirstOccurence(C, 108) ==  3);
  assert(FirstOccurence(C, 243) ==  5);
  assert(FirstOccurence(C, 285) ==  7);
  assert(FirstOccurence(C, 401) == 10);
  std::cout << "FirstOccurence test success" << std::endl;

  // testing FirstOccurence2
  assert(FirstOccurence2(C, -20) == -1);
  assert(FirstOccurence2(C,   0) == -1);
  assert(FirstOccurence2(C, 500) == -1);
  assert(FirstOccurence2(C, -14) ==  0);
  assert(FirstOccurence2(C, -10) ==  1);
  assert(FirstOccurence2(C,   2) ==  2);
  assert(FirstOccurence2(C, 108) ==  3);
  assert(FirstOccurence2(C, 243) ==  5);
  assert(FirstOccurence2(C, 285) ==  7);
  assert(FirstOccurence2(C, 401) == 10);
  std::cout << "FirstOccurence2 test success" << std::endl;

  return 0;
}
