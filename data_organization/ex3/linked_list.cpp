#include <cmath>
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

void remove(NODE** head_ref, int value) {
  NODE* prev = NULL;
  NODE* current = *head_ref;

  while (current != NULL) {
    if (current->data == value) {
      if (prev == NULL) {
        *head_ref = current->next;
      } else {
        prev->next = current->next;
      }
    }
    prev = current;
    current = current->next;
  }
}

void removeByRecurrsive(NODE** head_ref, int value) {
  if (*head_ref == NULL) return;

  if ((*head_ref)->data == value) {
    NODE* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    delete temp;
    removeByRecurrsive(head_ref, value);
  } else {
    removeByRecurrsive(&(*head_ref)->next, value);
  }
}

// Traverse from head toward the last and sum
int sumPosByIterative(NODE* head) {
  int total = 0;
  NODE* c = head;
  while (c != NULL) {
    total += c->data > 0 ? c->data : 0;
    c = c->next;
  }

  return total;
}

// Recursive
int sumPosByRecursive(NODE* head) {
  if (head == NULL) return 0;
  return (head->data > 0 ? head->data : 0) + sumPosByRecursive(head->next);
}

int main() {
  NODE* head = NULL;
  append(&head, 1);
  append(&head, 3);
  append(&head, -1);
  append(&head, 8);
  append(&head, -2);
  append(&head, 4);
  std::cout << "Tong (Su dung lap): " << sumPosByIterative(head) << std::endl;
  std::cout << "Tong (Su dung de quy): " << sumPosByRecursive(head)
            << std::endl;
  return 0;
}
