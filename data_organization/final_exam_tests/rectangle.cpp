/**
 * Gia su trong mot mat phang 2 chieu, ta can thao tac tren cac diem va cac hinh
 *nhu nhat. Cu the, ta noi mot diem nam trong mot hinh chu nhat neu diem do
 *thuoc hinh chu nhat va 2 hinh chu nhat roi nhau neu phan giao cua chung la
 *rong. Vi du, voi cac diem P1, P2 va cac hinh chu nhat H1, H2, H3 hu hinh duoi
 *day: Thi P1 nam trong H1, H2, nhung khong nam trong H3; P2 khong nam trong ca
 *3 hinh chu nhat H1, H2, H3; H2 va H3 roi nhau nhung H1 va H2 hay H1, va H3 thi
 *khong. Gia su cac diem va cac dinh hinh chu nhat deu co toa do nguyen, hay: a)
 *Mo ta cach to chuc du lieu cho cac diem va hinh chu nhat. Khai bao cau truc
 *struct. b) Viet ham kiem tra mot diem co nam trong mot hinh chu nhat hay
 *khong. c) Viet ham kiem tra hai hinh chu nhat co roi nhau hay khong.
 **/

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