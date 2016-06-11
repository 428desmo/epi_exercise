#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <stack>

template <typename T>
class Stack {
public:
  void Push(T e) {
    if (stack.empty())
      stack.emplace(MaxAndValue{e, e});
    else
      stack.emplace(MaxAndValue{std::max(e, stack.top().Max), e});
  }

  T Pop() {
    if (stack.empty())
      throw "Stack is empty";
    else {
      T value = stack.top().Value;
      stack.pop();
      return value;
    }
  }

  T Max() {
    if (stack.empty())
      throw "Stack is empty";
    else
      return stack.top().Max;
  }

  bool Empty() {
    return stack.empty();
  }

private:
  struct MaxAndValue{
    T Max;
    T Value;
  };
  std::stack<MaxAndValue> stack;
};

template <typename T>
class Stack2 {
public:
  void Push(T e) {
    element_stack.emplace(e);
    if (max_stack.empty() || Max() < e) {
      max_stack.emplace(MaxAndCount{e, 1});
    }
    else if (Max() == e) {
      int count = max_stack.top().Count;
      max_stack.pop();
      max_stack.push(MaxAndCount{e, count + 1});
    }
  }

  T Pop() {
    if (element_stack.empty())
      throw "Stack is empty";
    else {
      T value = element_stack.top();
      element_stack.pop();
      if (Max() == value) {
        int count = max_stack.top().Count;
        max_stack.pop();
        if (count > 1)
          max_stack.push(MaxAndCount{value, count - 1});
      }
      return value;
    }
  }

  T Max() {
    if (max_stack.empty())
      throw "Stack is empty";
    else
      return max_stack.top().Max;
  }

  bool Empty() {
    return element_stack.empty();
  }

private:
  struct MaxAndCount{
    T Max;
    int Count;
  };
  std::stack<T> element_stack;
  std::stack<MaxAndCount> max_stack;
};


int main(int argc, char* argv[])
{
  Stack<int> S1;
  S1.Push(1);
  S1.Push(7);
  S1.Push(5);
  S1.Push(3);
  S1.Push(5);
  S1.Push(8);
  S1.Push(9);
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl;
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl;
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl;
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl;
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl;
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl;
  std::cout << "Max: " << S1.Max() << ", Popd: " << S1.Pop() << std::endl << std::endl;

  Stack2<int> S2;
  S2.Push(1);
  S2.Push(7);
  S2.Push(5);
  S2.Push(3);
  S2.Push(5);
  S2.Push(8);
  S2.Push(9);
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;
  std::cout << "Max: " << S2.Max() << ", Popd: " << S2.Pop() << std::endl;


  return 0;
}
