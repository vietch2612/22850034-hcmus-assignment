#include <iostream>
using namespace std;

struct LIST {
  int data[1000];
  int length;
};

// [1, 2, 3, 4, 5] 5
void removeFirst(LIST &l) {
  for (int i = 0; i < l.length - 1; i++) {
    l.data[i] = l.data[i + 1];
  }
  l.length--;
}

// [1, 2, 3, 4], 4
void removeLast(LIST &l) { l.length--; }

// [1, 2, 3, 4, 5, 6], l=6, k=3
// [1, 2, 3, 5, 6], l=6, k=3
void removeAt(LIST &l, int k) {
  for (int i = k; i < l.length - 1; i++) {
    l.data[i] = l.data[i + 1];
  }
  l.length--;
}

// [1, 2, 3, 4, 5], l=5
// [1, 1, 2, 3, 4, 5]
void insertFirst(LIST &l, int x) {
  for (int i = l.length; i > 0; i--) {
    l.data[i] = l.data[i - 1];
  }
  l.data[0] = x;
  l.length++;
}

void insertLast(LIST &l, int x) {
  l.data[l.length] = x;
  l.length++;
}

// [1, 2, 3, 4, 5], l=5, k=3, x=6
void insertAt(LIST &l, int k, int x) {
  for (int i = l.length; i > k; i--) {
    l.data[i] = l.data[i - 1];
  }
  l.data[k] = x;
  l.length++;
}

void printList(LIST l) {
  for (int i = 0; i < l.length; i++) {
    cout << l.data[i] << " ";
  }
  cout << endl;
}

int main() {
  LIST l = {{1, 2, 3, 4, 5}, 5};
  insertFirst(l, 0);

  insertAt(l, 3, 6);

  printList(l);

  return 0;
}