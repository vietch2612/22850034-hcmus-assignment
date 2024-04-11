#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

int main() {
  Point point = {0x11, 0x22};
  int *p = &point.x;
  Point *pp = &point;
  char *q = (char *)pp;

  cout << "%x: " << *p << endl;
  cout << "%x: " << &p << endl;

  return 0;
}