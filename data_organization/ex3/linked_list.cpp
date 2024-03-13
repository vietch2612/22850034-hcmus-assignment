#include <iostream>

struct NODE {
  int data;
  NODE* next;
};

void append(NODE** head_ref, int value) {
  NODE* new_node = new NODE();
  new_node->data = value;
  new_node->next = NULL;

  // If *head_ref == NULL means new_node is head
  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }

  // Traverse to find the LAST node
  // Then update next to the new one
  NODE* last = *head_ref;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_node;
};

// Traverse from head toward the last and sum
int sumPosByIterative(NODE* head) {
  int total = 0;
  NODE* c = head;
  while (c != NULL) {
    total += c->data;
    c = c->next;
  }

  return total;
}

// Recursive
int sumPosByRecursive(NODE* head) {
  if (head == NULL) return 0;
  return head->data + sumPosByIterative(head->next);
}

int main() {
  NODE* head = NULL;
  append(&head, 1);
  append(&head, 3);
  append(&head, 3);
  append(&head, 8);
  append(&head, 2);
  append(&head, 4);
  std::cout << "Tong (Su dung lap): " << sumPosByIterative(head) << std::endl;
  std::cout << "Tong (Su dung de quy): " << sumPosByRecursive(head)
            << std::endl;
  return 0;
}
