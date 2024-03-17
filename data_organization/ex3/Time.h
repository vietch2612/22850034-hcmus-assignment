#include <iostream>
#include <sstream>

class Time {
 private:
  int hour, minute, second;

 public:
  // Validate the time format
  bool isValid() {
    bool isHourValid = false;
    bool isMinuteValid = false;
    bool isSecondValid = false;
    if (hour >= 0 && hour < 24) isHourValid = true;
    if (minute >= 0 && minute < 60) isMinuteValid = true;
    if (second >= 0 && second < 60) isSecondValid = true;

    return isHourValid && isMinuteValid && isSecondValid;
  }

  // C++ way to parse string instead of scanf
  static Time parseFromString(std::string& timeString) {
    Time t;
    std::stringstream ss(timeString);
    char discard;
    ss >> t.hour >> discard >> t.minute >> discard >> t.second;
    return t;
  }

  // Convert all to seconds and return sum
  int toSeconds() { return hour * 3600 + minute * 60 + second; }

  // Convert to seconds then compare
  static int secondDiff(Time& t1, Time& t2) {
    return t1.toSeconds() - t2.toSeconds();
  }

  // If this.time == anotherTime return 0;
  // If this.time > anotherTime return -1;
  // If this.time < anotherTime return 1;
  int compareTo(Time& anotherTime) {
    if (toSeconds() == anotherTime.toSeconds()) return 0;
    return toSeconds() < anotherTime.toSeconds() ? -1 : 1;
  }
};
