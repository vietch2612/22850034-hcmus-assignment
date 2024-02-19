#include <iostream>
void print_array(int a[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}

void remove_duplicate_values_in_place(int a[], int &n) {
  int index = 0;  // init a new index

  for (int i = 0; i < n; i++) {
    bool isDuplicate = false;

    // Loop from 0 to index to see if if a[k] is occured or not
    for (int k = 0; k < index; k++) {
      if (a[i] == a[k]) {
        isDuplicate = true;
        break;
      }
    }

    // If a[i] is not duplicated, re-update its index
    if (!isDuplicate) a[index++] = a[i];
  }

  // Update the size of the array after we removed the duplicate values
  n = index;
}

void remove_duplicate_values_out_place(int a[], int &n) {
  int newArray[n];
  int index = 0;

  for (int i = 0; i < n; i++) {
    bool isDuplicate = false;

    for (int k = 0; k < index; k++) {
      if (a[i] == newArray[k]) {
        isDuplicate = true;
        break;
      }
    }

    if (!isDuplicate) {
      newArray[index++] = a[i];
    }
  }

  // Update the array
  for (int i = 0; i < index; i++) {
    a[i] = newArray[i];
  }
  // Update the size of the array
  n = index;
}

int main() {
  std::cout << "In-place" << std::endl;

  int n;
  std::cout << "Nhap do dai cua mang n: ";
  std::cin >> n;

  std::cout << "Vui long nhap gia tri cua mang a: " << std::endl;
  int a[n];
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cout << std::endl;

  std::cout << "Original: " << std::endl;
  print_array(a, n);

  // Remove
  std::cout << "Removed: " << std::endl;
  remove_duplicate_values_in_place(a, n);
  print_array(a, n);

  return 0;
}
