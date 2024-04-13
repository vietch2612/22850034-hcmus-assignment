// Mot da thuc bang n (n >= 0) la mot bieu thuc co dang a0 + a1x + a2x^2 + ... +
// anx^n Trong do a0, a1, a2, ..., an la cac so thuc (an != 0) duoc goi la cac
// he so, ki hieu hinh thuc x duoc goi la bien Neu thay mot so thuc v vao bien x
// va thuc hien cac phep toan thi ta duoc ket qua la mot so thuc Goi la gia tri
// cua da thuc tai v. Vi do cho da thuc P(x) = 1 - 2x^2 + x^3 thi P(x) la da
// thuc bac 3 (n = 3) voi cac he so tuong ung a0 = 1, a1 = 0, a2 = -2, a3 = 1 Va
// cac gia tri cua P(x) tai 1 la P(1) = 1 - 2*1^2 + 1^3 = 1 - 2 + 1 = 0 Su dung
// Linked List, hay cai dat cac ham sau:

// Mo ta cac to chuc du lieu cho cac da thuc

#include <iostream>
using namespace std;

struct Node {
  float coefficient;
  int exponent;
  Node *next;
};

// Them mot monom vao da thuc
void add(Node *&head, float coefficient, int exponent) {
  Node *newNode = new Node;
  newNode->coefficient = coefficient;
  newNode->exponent = exponent;
  newNode->next = head;
  head = newNode;
}

// Tinh gia tri cua da thuc tai x

float evaluate(Node *head, float x) {
  float result = 0;
  Node *current = head;
  while (current != NULL) {
    result += current->coefficient * pow(x, current->exponent);
    current = current->next;
  }
  return result;
}

// In da thuc

void print(Node *head) {
  Node *current = head;
  while (current != NULL) {
    cout << current->coefficient << "x^" << current->exponent;
    if (current->next != NULL) {
      cout << " + ";
    }
    current = current->next;
  }
  cout << endl;
}

int main() {
  Node *head = NULL;
  add(head, 1, 0);
  add(head, 0, 1);
  add(head, -2, 2);
  add(head, 1, 3);
  print(head);
  cout << "P(1) = " << evaluate(head, 1) << endl;
  return 0;
}