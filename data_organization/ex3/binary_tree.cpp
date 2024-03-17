#include <iostream>

struct NODE {
  int data;
  NODE *left, *right;
};

// Sum using recursive
int sumPos(NODE* root) {
  if (root == NULL) return 0;
  return (root->data > 0 ? root->data : 0) + sumPos(root->left) +
         sumPos(root->right);
};

// Support method
// To create a new node faster
NODE* newNode(int value) {
  NODE* node = new NODE();
  node->data = value;
  return node;
}

int main() {
  // Create a new node to test
  NODE* root = newNode(8);
  root->left = newNode(-4);
  root->right = newNode(1);
  root->left->left = newNode(-3);
  root->left->right = newNode(-2);
  root->right->left = newNode(5);
  root->right->right = newNode(7);

  std::cout << "Tong cua cay = " << sumPos(root) << std::endl;
}
