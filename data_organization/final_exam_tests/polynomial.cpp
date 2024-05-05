#include <iostream>
using namespace std;

struct Node {
  float coefficient;
  int exponent;
  Node *next;
};

// Add a new term to the polynomial
void add(Node *&head, float coefficient, int exponent) {
  Node *newNode = new Node;
  newNode->coefficient = coefficient;
  newNode->exponent = exponent;
  newNode->next = head;
  head = newNode;
}

// Evaluate the polynomial at x
float evaluate(Node *head, float x) {
  float result = 0;
  Node *current = head;
  while (current != NULL) {
    result += current->coefficient * pow(x, current->exponent);  // Cong thuc
    current = current->next;
  }
  return result;
}

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
  // 1*x^0 + 0xx1 + (-2)x^2 + 1 * x^3
  Node *head = NULL;
  add(head, 1, 0);
  add(head, 0, 1);
  add(head, -2, 2);
  add(head, 1, 3);
  print(head);
  cout << "P(1) = " << evaluate(head, 1) << endl;
  return 0;
}