#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
//#include <memory>

template<typename T>
struct BSTNode {
  BSTNode() {}
  BSTNode(T _data)
    : data(_data), left(), right() {}

  void operator=(const BSTNode& that) {
    data = that.data;
    left = that.left;
    right = that.right;
  }

  T data;
  std::unique_ptr<BSTNode<T>> left, right;
};

BSTNode<int>* SearchBST(const std::unique_ptr<BSTNode<int>>& tree, int key)
{
  if (tree == NULL) {
    return NULL;
  }
  if (tree->data == key) {
    return tree.get();
  }
  return key < tree->data ? SearchBST(tree->left, key) : SearchBST(tree->right, key);
}

void DebugPrint(const std::unique_ptr<BSTNode<int>>& node)
{
  if (node) {
    printf("this=%d, left=%d, right=%d\n", node->data, node->left ? node->left->data : -1, node->right ? node->right->data : -1);
    DebugPrint(node->left);
    DebugPrint(node->right);
  }
}

// return false if duplicate
bool InsertNode(std::unique_ptr<BSTNode<int>>& tree, int key)
{
  if (tree == NULL) {
    tree = std::unique_ptr<BSTNode<int>>(new BSTNode<int>(key));
    return true;
  }
  if (key <= tree->data) {
    if (tree->left) {
      return InsertNode(tree->left, key);
    }
    else {
      tree->left = std::unique_ptr<BSTNode<int>>(new BSTNode<int>(key));
    }
  }
  else if (key > tree->data) {
    if (tree->right) {
      return InsertNode(tree->right, key);
    }
    else {
      tree->right = std::unique_ptr<BSTNode<int>>(new BSTNode<int>(key));
    }
  }
  return false;
}


template <typename T>
struct BinaryTreeNode {
  T data;
  std::unique_ptr<BinaryTreeNode<T>> left, right;
};

template <typename T>
void InitNode(std::unique_ptr<BinaryTreeNode<T>>& node, T value)
{
  node = std::unique_ptr<BinaryTreeNode<T>>(new BinaryTreeNode<T>);
  node->data = value;
}

void DebugPrint(const std::unique_ptr<BinaryTreeNode<int>>& node)
{
  if (node) {
    printf("this=%d, left=%d, right=%d\n", node->data, node->left ? node->left->data : -1, node->right ? node->right->data : -1);
    DebugPrint(node->left);
    DebugPrint(node->right);
  }
}

bool AreKeysInRange(const std::unique_ptr<BinaryTreeNode<int>>& tree, int low_range, int high_range)
{
  if (tree == NULL) {
    return true;
  }
  else if (tree->data < low_range || tree->data > high_range) {
    return false;
  }
  return AreKeysInRange(tree->left, low_range, tree->data) && AreKeysInRange(tree->right, tree->data + 1, high_range);
}

bool IsBinaryTreeBST(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
  return AreKeysInRange(tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}



int main(int argc, char* argv[])
{
  std::unique_ptr<BSTNode<int>> tree(new BSTNode<int>(19));
  InsertNode(tree, 7);
  InsertNode(tree, 3);
  InsertNode(tree, 2);
  InsertNode(tree, 5);
  InsertNode(tree, 11);
  InsertNode(tree, 17);
  InsertNode(tree, 13);
  InsertNode(tree, 43);
  InsertNode(tree, 23);
  InsertNode(tree, 37);
  InsertNode(tree, 29);
  InsertNode(tree, 31);
  InsertNode(tree, 41);
  InsertNode(tree, 47);
  InsertNode(tree, 53);
  printf("tree\n");
  DebugPrint(tree);

  printf("\n");
  std::unique_ptr<BinaryTreeNode<int>> tree2(new BinaryTreeNode<int>);
  InitNode(tree2, 19);
  InitNode(tree2->left, 7);
  InitNode(tree2->left->left, 3);
  InitNode(tree2->left->left->left, 2);
  InitNode(tree2->left->left->right, 5);
  InitNode(tree2->left->right, 11);
  InitNode(tree2->left->right->right, 17);
  InitNode(tree2->left->right->right->left, 13);
  InitNode(tree2->right, 43);
  InitNode(tree2->right->left, 23);
  InitNode(tree2->right->left->right, 37);
  InitNode(tree2->right->left->right->left, 29);
  InitNode(tree2->right->left->right->left->right, 31);
  InitNode(tree2->right->left->right->right, 41);
  InitNode(tree2->right->right, 47);
  InitNode(tree2->right->right->right, 53);
  printf("tree2\n");
  DebugPrint(tree2);
  assert(IsBinaryTreeBST(tree2));
  printf("tree2 is BST\n");

  InitNode(tree2->right->right->right->left, 40);
  printf("tree2\n");
  DebugPrint(tree2);
  assert(!IsBinaryTreeBST(tree2));
  printf("tree2 is not BST any longer\n");

  


  return 0;
}
