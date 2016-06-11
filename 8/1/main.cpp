#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>

template <typename T>
class ListNode
{
public:
  ListNode() : val(-1), next(NULL) {}
  ListNode(int val) : val(val), next(NULL) {}
  ~ListNode() {}
  T val;
  std::shared_ptr<ListNode<T>> next;
};

template <typename T>
void InsertAfter(std::shared_ptr<ListNode<T>>& node,
                 std::shared_ptr<ListNode<T>>& new_node)
{
  new_node->next = node->next;
  node->next = new_node;
}

template <typename T>
void AppendNode(std::shared_ptr<ListNode<T>>* node,
                std::shared_ptr<ListNode<T>>* tail)
{
  (*tail)->next = *node;
  *tail = *node;
  *node = (*node)->next;

}

template <typename T>
void DeleteAfter(std::shared_ptr<ListNode<T>>& node)
{
  if (node->next)
    node->next = node->node->next;
}

template <typename T>
std::shared_ptr<ListNode<T>> SearchList(std::shared_ptr<ListNode<T>>& ListHead, T key)
{
  std::shared_ptr<ListNode<T>>& cur = ListHead;
  while (cur && cur->val != key)
    cur = cur->next;

  // now cur is NULL (not found), or the node which is looked for
  return cur;
}

template <typename T>
class List
{
public:
  List() : head(NULL), tail(NULL) {}
  ~List() {}

  void Append(std::shared_ptr<ListNode<T>> new_node) {
    if (!head)
      head = tail = new_node;
    else {
      InsertAfter(tail, new_node);
      tail = new_node;
    }
  }

  void DebugPrint(const char* msg=NULL) {
    std::shared_ptr<ListNode<T>> cur = head;
    if (msg)
      std::cout << msg << "\t";
    while (cur) {
      std::cout << cur->val << " ";
      cur = cur->next;
    }
    std::cout << std::endl;
  }

  std::shared_ptr<ListNode<T>> head;
  std::shared_ptr<ListNode<T>> tail;
};

template <typename T>
List<T> Merge(List<T>& L1, List<T>& L2)
{
  List<T> L;
  std::shared_ptr<ListNode<T>> n1 = L1.head;
  std::shared_ptr<ListNode<T>> n2 = L2.head;
  while (n1 && n2) {
    if (n1->val <= n2->val) {
      L.Append(std::make_shared<ListNode<int>>(n1->val));
      n1 = n1->next;
    }
    else {
      L.Append(std::make_shared<ListNode<int>>(n2->val));
      n2 = n2->next;
    }
  }
  while (n1) {
    L.Append(std::make_shared<ListNode<int>>(n1->val));
    n1 = n1->next;
  }
  while (n2) {
    L.Append(std::make_shared<ListNode<int>>(n2->val));
    n2 = n2->next;
  }
  return L;
}

template <typename T>
List<T> Merge2(List<T>& L1, List<T>& L2)
{
  auto n1 = L1.head;
  auto n2 = L2.head;
  std::shared_ptr<ListNode<T>> dummy_head = std::make_shared<ListNode<T>>();
  auto tail = dummy_head;

  while (n1 && n2) {
    AppendNode(n1->val <= n2->val ? &n1 : &n2 , &tail);
  }
  tail->next = n1 ? n1 : n2;

  List<T> L;
  L.Append(dummy_head->next);
  return L;
}


int main(int argc, char* argv[])
{
  std::shared_ptr<ListNode<int>> n = std::make_shared<ListNode<int>>(2);
  
  List<int> L1;
  L1.Append(std::make_shared<ListNode<int>>(2));
  L1.DebugPrint("L1");
  L1.Append(std::make_shared<ListNode<int>>(5));
  L1.DebugPrint("L1");
  L1.Append(std::make_shared<ListNode<int>>(7));
  L1.DebugPrint("L1");

  List<int> L2;
  L2.Append(std::make_shared<ListNode<int>>(3));
  L2.Append(std::make_shared<ListNode<int>>(11));
  L2.DebugPrint("L2");

  List<int> L3 = Merge(L1, L2);
  L3.DebugPrint("L3");

  List<int> L4 = Merge2(L1, L2);
  L4.DebugPrint("L4");

  return 0;
}
