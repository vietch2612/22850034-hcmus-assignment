#include <iostream>

struct NODE {
  int data;
  NODE *left, *right;
};

int sumPos(NODE* root) {
  if (root == NULL) return 0;
  return root->data + sumPos(root->left) + sumPos(root->right);
};

NODE* newNode(int value) {
  NODE* node = new NODE();
  node->data = value;
  return node;
}

int main() {
  NODE* root = newNode(8);
  root->left = newNode(4);
  root->right = newNode(1);
  root->left->left = newNode(3);
  root->left->right = newNode(2);
  root->right->left = newNode(5);
  root->right->right = newNode(7);

  std::cout << "Tong cua cay = " << sumPos(root) << std::endl;
}
