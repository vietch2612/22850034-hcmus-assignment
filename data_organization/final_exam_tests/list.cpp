#include <iostream>
using namespace std;

struct LIST {
  int data[1000];
  int length;
};

void removeFirst(LIST &l) {
  for (int i = 0; i < l.length - 1; i++) {
    l.data[i] = l.data[i + 1];
  }
  l.length--;
}

void removeLast(LIST &l) { l.length--; }

void removeAt(LIST &l, int k) {
  for (int i = k; i < l.length - 1; i++) {
    l.data[i] = l.data[i + 1];
  }
  l.length--;
}

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