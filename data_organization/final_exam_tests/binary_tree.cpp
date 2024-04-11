#include <iostream>
using namespace std;

struct NODE {
  int data;
  NODE *left, *right;
};

int count(NODE *root) {
  return root == NULL ? 0 : 1 + count(root->left) + count(root->right);
};

int sum(NODE *root) {
  return root == NULL ? 0 : root->data + sum(root->left) + sum(root->right);
};

int balanced(NODE *root) {
  if (root == NULL) return 1;
  int left = count(root->left);
  int right = count(root->right);
  return abs(left - right) <= 1 && balanced(root->left) &&
         balanced(root->right);
};