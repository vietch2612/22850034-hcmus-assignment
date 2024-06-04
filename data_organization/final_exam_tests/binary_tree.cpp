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

// Recurrsive
NODE *max(NODE *root) {
  if (root == NULL) {
    return NULL;
  }

  NODE *maxLeft = max(root->left);
  NODE *maxRight = max(root->right);
  NODE *max = root;

  if (maxLeft != NULL && maxLeft->data > max->data) {
    max = maxLeft;
  }

  if (maxRight != NULL && maxRight->data > max->data) {
    max = maxRight;
  }

  return max;
};

int main() {
  NODE *root = new NODE;
  root->data = 1;
  root->left = new NODE;
  root->left->data = 2;
  root->left->left = new NODE;
  root->left->left->data = 3;
  root->left->right = new NODE;
  root->left->right->data = 4;
  root->right = new NODE;
  root->right->data = 5;
  root->right->left = new NODE;
  root->right->left->data = 6;
  root->right->right = new NODE;
  root->right->right->data = 7;

  cout << "Count: " << count(root) << endl;
  cout << "Sum: " << sum(root) << endl;
  cout << "Balanced: " << balanced(root) << endl;
  cout << "Max: " << max(root)->data << endl;

  return 0;
}