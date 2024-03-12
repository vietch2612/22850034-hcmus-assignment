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
      reOrder();
    };
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
  bool isEqual(Bag& anotherBag) {
    // Check the size if equal
    if (size != anotherBag.size) return false;

    int count[MAX_VALUE] = {0};
    for (int i = 0; i < size; i++) count[values[i]]++;
    for (int i = 0; i < size; i++) count[anotherBag.values[i]]--;
    for (int i = 0; i < size; i++)
      if (count[i] != 0) return false;
    return true;
  }

  // Check if this bag is subset of another bag
  // This way, it would take more time than the way I'm using in isEqual()
  bool isSubsetOf(Bag& anotherBag) {
    for (int i = 0; i < size; i++)
      if (count(values[i] > anotherBag.count(values[i]))) return false;
    return true;
  }

  // Merge two bags
  void merge(Bag& anotherBag) {
    for (int i = 0; i < anotherBag.size; i++)
      values[size++] = anotherBag.values[i];
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
  bag1.print();
  bag1.insert(2);
  bag1.print();
  bag1.insert(1);
  bag1.print();
  bag1.insert(3);
  bag1.print();
  bag1.removeAll(1);
  bag1.print();
  bag1.insert(10);
  bag1.print();

  Bag bag2;
  bag2.insert(4);
  bag2.insert(5);
  bag2.print();
  bag2.insert(5);
  bag2.print();
  bag1.merge(bag2);
  bag1.print();
  std::cout << "5: " << bag1.count(5) << std::endl;

  Bag bag3;
  bag3.insert(5);
  bag3.insert(2);
  bag3.insert(4);
  bag3.insert(10);
  bag3.insert(3);
  bag3.insert(5);
  bag1.print();
  bag2.print();
  bag3.print();
  std::cout << bag1.isEqual(bag2) << std::endl;
  std::cout << bag1.isEqual(bag3) << std::endl;

  Bag bag4;
  bag4.insert(2);
  bag4.insert(5);
  std::cout << "Is subset of?: " << bag4.isSubsetOf(bag1) << std::endl;
  return 0;
}
