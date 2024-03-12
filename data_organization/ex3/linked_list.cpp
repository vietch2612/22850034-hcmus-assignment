#include <iostream>

struct NODE {
  int data;
  NODE* next;
};

void append(NODE** head_ref, int value) {
  NODE* new_node = new NODE();
  new_node->data = value;
  new_node->next = NULL;
  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }

  // Traverse to find the last NODE
  // Then update next to the new one
  NODE* last = *head_ref;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_node;
};

int sumByIterative(NODE* head) {
  int total = 0;
  NODE* c = head;
  while (c != NULL) {
    total += c->data;
    c = c->next;
  }

  return total;
}

int sumByRecursive(NODE* head) {
  if (head == NULL) return 0;
  return head->data + sumByIterative(head->next);
}

int main() {
  NODE* head = NULL;
  append(&head, 1);
  append(&head, 3);
  append(&head, 3);
  append(&head, 8);
  append(&head, 2);
  append(&head, 4);
  std::cout << "Tong (Su dung lap): " << sumByIterative(head) << std::endl;
  std::cout << "Tong (Su dung de quy): " << sumByRecursive(head) << std::endl;
  return 0;
}
