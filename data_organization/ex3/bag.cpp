#include <iostream>

#define NOT_A_VALUE -1
#define MAX_VALUE 1000

class Bag {
 private:
  int size = 0;
  int values[MAX_VALUE] = {NOT_A_VALUE};

  void removeAt(int index) { values[index] = NOT_A_VALUE; }

  void reOrder() {
    int j = 0;
    for (int i = 0; i < size; i++) {
      if (values[i] != NOT_A_VALUE) {
        values[j] = values[i];
        j++;
      }
    }
    size = j;
  }

 public:
  Bag() {}

  // Insert a new value
  void insert(int value) { values[size++] = value; };

  // Remove a single element
  void remove(int value) {
    for (int i = 0; i < size; i++) {
      if (value == values[i]) {
        removeAt(i);
        break;
      }
    };
    reOrder();
  }

  // Remove all
  void removeAll(int value) {
    for (int i = 0; i < size; i++)
      if (value == values[i]) removeAt(i);
    reOrder();
  };

  // Count
  int count(int value) {
    int c = 0;
    for (int i = 0; i < size; i++)
      if (values[i] == value) c++;
    return c;
  }

  // Check if two bags are equal
  bool isEqual(Bag& aBag) {
    // Check the size if equal
    if (size != aBag.size) return false;

    // Init an array to store the count of each value
    int count[MAX_VALUE] = {0};
    // Then count the number of each value in this.bag
    for (int i = 0; i < size; i++) count[values[i]]++;
    // Then decrease the count of each value in another bag aBag
    for (int i = 0; i < size; i++) count[aBag.values[i]]--;
    // If all the count is 0, then the two bags are equal
    for (int i = 0; i < size; i++)
      if (count[i] != 0) return false;
    return true;
  }

  // Check if this bag is subset of another bag
  // This way, it would take more time than the way I'm using in isEqual()
  bool isSubsetOf(Bag& aBag) {
    for (int i = 0; i < size; i++)
      if (count(values[i]) > aBag.count(values[i])) return false;
    return true;
  }

  // Merge two bags
  void merge(Bag& aBag) {
    for (int i = 0; i < aBag.size; i++) values[size++] = aBag.values[i];
  };

  // Print the list of values, for debugging purpose
  void print() {
    for (int i = 0; i < size; i++) std::cout << values[i] << ", ";
    std::cout << std::endl;
  };
};

int main() {
  Bag bag1;
  bag1.insert(1);
  bag1.insert(2);
  bag1.insert(1);
  bag1.insert(3);
  bag1.insert(3);
  bag1.insert(5);
  bag1.insert(5);
  bag1.insert(7);
  bag1.insert(7);
  bag1.insert(7);
  std::cout << "Tui 1: ";
  bag1.print();
  std::cout << std::endl;

  std::cout << "Them mot so 4: ";
  bag1.insert(4);
  bag1.print();
  std::cout << std::endl;

  std::cout << "Xoa so 1: ";
  bag1.remove(1);
  bag1.print();
  std::cout << std::endl;

  std::cout << "Xoa toan bo so 5: ";
  bag1.removeAll(5);
  bag1.print();
  std::cout << std::endl;

  std::cout << "So lan xuat hien cua so 1: " << bag1.count(1) << std::endl;
  std::cout << "So lan xuat hien cua so 5: " << bag1.count(5) << std::endl;
  std::cout << "So lan xuat hien cua so 7: " << bag1.count(7) << std::endl;
  std::cout << std::endl;

  Bag bag2;
  Bag bag3;
  bag2 = bag1;
  bag3 = bag1;
  bag3.remove(7);
  std::cout << "Tui 1: ";
  bag1.print();
  std::cout << "Tui 2: ";
  bag2.print();
  std::cout << "Tui 3: ";
  bag3.print();
  std::cout << "Tui 1 co bang tui 2 khong?: " << bag1.isEqual(bag2)
            << std::endl;
  std::cout << "Tui 1 co bang tui 3 khong?: " << bag1.isEqual(bag3)
            << std::endl;
  std::cout << "Tui 1 co co phai tui con cua 2 khong?: "
            << bag1.isSubsetOf(bag2) << std::endl;
  std::cout << "Tui 1 co co phai tui con cua 3 khong?: "
            << bag1.isSubsetOf(bag3) << std::endl;
  std::cout << "Tui 3 co co phai tui con cua 1 khong?: "
            << bag3.isSubsetOf(bag1) << std::endl;
  std::cout << std::endl;

  Bag bag4;
  bag4.insert(8);
  bag4.insert(20);
  std::cout << "Tui 4: ";
  bag4.print();
  std::cout << "Tui 1 + tui 4 se la: ";
  bag1.merge(bag4);
  bag1.print();

  return 0;
}
