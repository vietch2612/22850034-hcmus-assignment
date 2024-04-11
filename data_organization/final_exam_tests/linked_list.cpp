#include <iostream>
using namespace std;

struct NODE {
  int data;
  NODE *next;
};

void add(NODE *&head, int x) {
  NODE *newNode = new NODE;
  newNode->data = x;
  newNode->next = head;
  head = newNode;
}

void remove(NODE *&head, int x) {
  NODE *prev = NULL;
  NODE *current = head;

  while (current != NULL) {
    if (current->data == x) {
      if (prev == NULL) {
        head = current->next;
      } else {
        prev->next = current->next;
      }
    }
    prev = current;
    current = current->next;
  }
}

void removeByRecurrsive(NODE *&head, int x) {
  if (head == NULL) return;

  if (head->data == x) {
    NODE *temp = head;
    head = head->next;
    delete temp;
    removeByRecurrsive(head, x);
  } else {
    removeByRecurrsive(head->next, x);
  }
}

int main() {
  NODE *head = new NODE;
  head->data = 1;
  head->next = new NODE;
  head->next->data = 2;
  head->next->next = new NODE;
  head->next->next->data = 3;
  head->next->next->next = NULL;

  removeByRecurrsive(head, 2);

  NODE *current = head;
  while (current != NULL) {
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;

  return 0;
}