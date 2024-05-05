#include <iostream>
using namespace std;

struct NODE {
  int data;
  NODE *left, *right;
};

// Count all nodes in the tree
// Recurrsive
int count(NODE *root) {
  if (root == NULL) {
    return 0;
  }

  return 1 + count(root->left) + count(root->right);
};

int sum(NODE *root) {
  if (root == NULL) {
    return 0;
  }

  return root->data + sum(root->left) + sum(root->right);
};

// Check if the tree is balanced
int balanced(NODE *root) {
  if (root == NULL) {
    return 1;
  };

  int left = count(root->left);
  int right = count(root->right);
  return abs(left - right) <= 1 && balanced(root->left) &&
         balanced(root->right);
};