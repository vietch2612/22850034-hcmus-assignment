#include <iostream>

int value_of_roman(char c) {
  switch (c) {
    case 'I':
      return 1;
    case 'V':
      return 5;
    case 'X':
      return 10;
    case 'L':
      return 50;
    case 'C':
      return 100;
    case 'D':
      return 500;
    case 'M':
      return 1000;
    default:
      return -1;
  }
}

int roman_to_int(std::string s) {
  int result = 0;

  // If s[i] >= s[i+1] then result += s[i]
  // If s[i] < s[i+1] then result += s[i] - s[i+1]
  // And ignore the value at a[i+1]
  for (int i = 0; i < s.length(); i++) {
    int num1 = value_of_roman(s[i]);

    if (i < s.length() - 1) {  // Don't need to check if it's the last char
      int num2 = value_of_roman(s[i + 1]);

      if (num1 >= num2) {
        result += num1;
      } else {
        result += num2 - num1;
        i++;  // Ignore the next i
      }
    } else {
      result += num1;
    }
  }

  return result;
}

int main() {
  // Exercise 4.4.7 / Question 4.
  std::cout << "Vui long nhap so Roman: ";
  std::string roman;
  std::cin >> roman;

  std::cout << "So roman " << roman << " tuong ung: " << roman_to_int(roman)
            << std::endl;

  return 0;
}
