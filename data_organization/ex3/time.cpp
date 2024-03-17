#include "Time.h"

#include <iostream>

int main() {
  std::string timeString1, timeString2;

  std::cout << "Nhap thoi diem thu nhat HH:MM:SS: ";
  std::cin >> timeString1;
  Time time1 = Time::parseFromString(timeString1);
  std::cout << "Nhap thoi diem thu hai HH:MM:SS: ";
  std::cin >> timeString2;
  Time time2 = Time::parseFromString(timeString2);

  if (!time1.isValid() && !time2.isValid()) {
    std::cout << "Thoi gian khong hop le" << std::endl;
    return 1;
  }
  std::cout << "Thoi gian hop le." << std::endl;

  int secondDiff = Time::secondDiff(time1, time2);
  if (secondDiff == 0) {
    std::cout << "Hai thoi diem nay trung nhau";
  } else if (secondDiff > 0) {
    std::cout << "Thoi diem thu 2 dien ra truoc";
  } else {
    std::cout << "Thoi diem thu nhat dien ra truoc";
  }
  std::cout << std::endl;

  std::cout << "Tong so giay giua hai thoi diem: " << std::abs(secondDiff)
            << std::endl;

  return 0;
}
