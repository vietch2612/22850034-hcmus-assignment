#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

struct Rectangle {
  Point topLeft, bottomRight;
};

bool isPointInRectangle(Point p, Rectangle r) {
  return p.x >= r.topLeft.x && p.x <= r.bottomRight.x &&
         p.y >= r.bottomRight.y && p.y <= r.topLeft.y;
}

bool isRectangleOverlap(Rectangle r1, Rectangle r2) {
  return r1.topLeft.x < r2.bottomRight.x && r1.bottomRight.x > r2.topLeft.x &&
         r1.topLeft.y > r2.bottomRight.y && r1.bottomRight.y < r2.topLeft.y;
}

int main() {
  Point p1 = {1, 1};
  Point p2 = {2, 2};
  Rectangle r1 = {{0, 3}, {3, 0}};
  Rectangle r2 = {{1, 4}, {4, 1}};
  Rectangle r3 = {{4, 5}, {5, 4}};

  cout << "P1 is in R1: " << isPointInRectangle(p1, r1) << endl;
  cout << "P1 is in R2: " << isPointInRectangle(p1, r2) << endl;
  cout << "P1 is in R3: " << isPointInRectangle(p1, r3) << endl;
  cout << "P2 is in R1: " << isPointInRectangle(p2, r1) << endl;
  cout << "P2 is in R2: " << isPointInRectangle(p2, r2) << endl;
  cout << "P2 is in R3: " << isPointInRectangle(p2, r3) << endl;

  cout << "R1 and R2 overlap: " << isRectangleOverlap(r1, r2) << endl;
  cout << "R1 and R3 overlap: " << isRectangleOverlap(r1, r3) << endl;
  cout << "R2 and R3 overlap: " << isRectangleOverlap(r2, r3) << endl;

  return 0;
}