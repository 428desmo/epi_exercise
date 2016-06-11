#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>

template <typename T>
struct BinaryTreeNode {
  T data;
  std::unique_ptr<BinaryTreeNode<T>> left, right;
};

template <typename T>
void TreeTraversal(const std::unique_ptr<BinaryTreeNode<T>>& root)
{
  if (root) {
    std::cout << "preorder: " << root->data << std::endl;
    TreeTraversal(root->left);
    std::cout << "inorder: " << root->data << std::endl;
    TreeTraversal(root->right);
    std::cout << "postorder: " << root->data << std::endl;
  }
}

// returned depth is incorrect.
template <typename T>
int TreeDepth(const std::unique_ptr<BinaryTreeNode<T>>& root)
{
  if (root) {
    int left_sub_depth = TreeDepth(root->left);
    if (left_sub_depth >= 0) {
      int right_sub_depth = TreeDepth(root->right);
      if (right_sub_depth >= 0) {
        int diff = left_sub_depth - right_sub_depth;
        if (std::abs(diff) <= 1)
          return std::max(left_sub_depth, right_sub_depth) + 1;
      }
    }
    return -1;
  }
  return 0;
}

template <typename T>
bool IsBalancedTree(const std::unique_ptr<BinaryTreeNode<T>>& root)
{
  return TreeDepth(root) >= 0;
}

struct Status {
  bool balanced;
  int height;
};

template <typename T>
Status CheckBalanced(std::unique_ptr<BinaryTreeNode<T>>& root)
{
  if (!root)
    return {true, -1};

  auto left_result = CheckBalanced(root->left);
  if (!left_result.balanced)
    return {false, 0};

  auto right_result = CheckBalanced(root->right);
  if (!right_result.balanced)
    return {false, 0};

  bool is_balanced = std::abs(left_result.height - right_result.height) <= 1;
  int height = std::max(left_result.height, right_result.height) + 1;
  return {is_balanced, height};
}

template <typename T>
bool IsBalancedTree2(std::unique_ptr<BinaryTreeNode<T>>& root)
{
  return CheckBalanced(root).balanced;
}

template <typename T>
void InitNode(std::unique_ptr<BinaryTreeNode<T>>& node, T value)
{
  node = std::unique_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>);
  node->data = value;
}

int main(int argc, char* argv[])
{
/*
  std::unique_ptr<BinaryTreeNode<int>> tree(new BinaryTreeNode<int>);
  InitNode(tree, 314);
  InitNode(tree->left, 6);
  InitNode(tree->left->left, 271);
  InitNode(tree->left->left->left, 28);
  InitNode(tree->left->left->right, 0);
  InitNode(tree->left->right, 561);
  InitNode(tree->left->right->right, 3);
  InitNode(tree->left->right->right->left, 17);
  InitNode(tree->right, 6);
  InitNode(tree->right->left, 2);
  InitNode(tree->right->left->right, 1);
  InitNode(tree->right->left->right->left, 401);
  InitNode(tree->right->left->right->left->right, 641);
  InitNode(tree->right->left->right->right, 257);
  InitNode(tree->right->right, 271);
  InitNode(tree->right->right->right, 28);
  TreeTraversal(tree);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree) ? "yes" : "no") << std::endl;
*/

  std::unique_ptr<BinaryTreeNode<int>> tree2(new BinaryTreeNode<int>);
  InitNode(tree2, 314);
  InitNode(tree2->left, 6);
  InitNode(tree2->left->left, 271);
  InitNode(tree2->left->right, 0);
  InitNode(tree2->right, 6);
  InitNode(tree2->right->left, 2);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree2) ? "yes" : "no") << std::endl;
  std::cout << "IsBalanced2? " << (IsBalancedTree2(tree2) ? "yes" : "no") << std::endl;

  InitNode(tree2->right->right, 271);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree2) ? "yes" : "no") << std::endl;
  std::cout << "IsBalanced2? " << (IsBalancedTree2(tree2) ? "yes" : "no") << std::endl;

  InitNode(tree2->left->left->left, 28);
  InitNode(tree2->left->left->right, 0);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree2) ? "yes" : "no") << std::endl;
  std::cout << "IsBalanced2? " << (IsBalancedTree2(tree2) ? "yes" : "no") << std::endl;

  InitNode(tree2->right->left->right, 1);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree2) ? "yes" : "no") << std::endl;
  std::cout << "IsBalanced2? " << (IsBalancedTree2(tree2) ? "yes" : "no") << std::endl;

  InitNode(tree2->right->left->right->left, 401);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree2) ? "yes" : "no") << std::endl;
  std::cout << "IsBalanced2? " << (IsBalancedTree2(tree2) ? "yes" : "no") << std::endl;

  InitNode(tree2->right->left->right->left->right, 641);
  std::cout << "IsBalanced? " << (IsBalancedTree(tree2) ? "yes" : "no") << std::endl;
  std::cout << "IsBalanced2? " << (IsBalancedTree2(tree2) ? "yes" : "no") << std::endl;



  return 0;
}
