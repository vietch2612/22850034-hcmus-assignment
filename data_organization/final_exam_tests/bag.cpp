#include <iostream>
using namespace std;

struct LIST {
  int data[1000];
  int length;
};

void insertLast(LIST &l, int x) {
  l.data[l.length] = x;
  l.length++;
}

void removeAt(LIST &l, int index) {
  for (int i = index; i < l.length - 1; i++) {
    l.data[i] = l.data[i + 1];
  }
  l.length--;
}

void removeOne(LIST &l, int x) {
  for (int i = 0; i < l.length; i++) {
    if (l.data[i] == x) {
      removeAt(l, i);
      break;
    }
  }
}

void removeAll(LIST &l, int x) {
  for (int i = 0; i < l.length; i++) {
    if (l.data[i] == x) {
      removeAt(l, i);
    }
  }
}

int count(LIST &l, int x) {
  int count = 0;
  for (int i = 0; i < l.length; i++) {
    if (l.data[i] == x) {
      count += 1;
    }
  }

  return count;
}

int isEqual(LIST &l1, LIST &l2) {
  if (l1.length != l2.length) {
    return 0;
  }

  int count_value[100] = {0};
  for (int i = 0; i < l1.length; i++) {
    count_value[l1.data[i]]++;
  }

  for (int i = 0; i < l2.length; i++) {
    count_value[l2.data[i]]--;
  }

  for (int i = 0; i < 100; i++) {
    if (count_value[i] != 0) {
      return 0;
    }
  }

  return 1;
}

int isSubBag(LIST &l1, LIST &l2) {
  int count1[100] = {0};
  int count2[100] = {0};

  for (int i = 0; i < l1.length; i++) {
    count1[l1.data[i]]++;
  }
  for (int i = 0; i < l2.length; i++) {
    count2[l2.data[i]]++;
  }

  for (int i = 0; i < 100; i++) {
    if (count1[i] > count2[i]) {
      return 0;
    }
  }

  return 1;
}

void merge(LIST &l1, LIST &l2) {
  int count1[100] = {0};
  int count2[100] = {0};

  for (int i = 0; i < l1.length; i++) {
    count1[l1.data[i]]++;
  }
  for (int i = 0; i < l2.length; i++) {
    count2[l2.data[i]]++;
  }

  for (int i = 0; i < 100; i++) {
    if (count1[i] == 0 || count2[i] == 0) {
      removeAll(l1, i);
    } else {
      for (int j = 0; j < count2[i]; j++) {
        insertLast(l1, i);
      }
    }
  }
}

void printList(LIST l) {
  for (int i = 0; i < l.length; i++) {
    cout << l.data[i] << " ";
  }
  cout << endl;
}

int main() {
  LIST l1;
  l1.length = 0;

  LIST l2;
  l2.length = 0;

  insertLast(l1, 1);
  insertLast(l1, 4);
  insertLast(l1, 2);

  insertLast(l2, 4);
  insertLast(l2, 1);
  insertLast(l2, 1);
  insertLast(l2, 2);
  insertLast(l2, 2);
  insertLast(l2, 3);

  // l3 = {1,1,1,2,2,2}

  merge(l1, l2);

  printList(l1);
  return 0;
}