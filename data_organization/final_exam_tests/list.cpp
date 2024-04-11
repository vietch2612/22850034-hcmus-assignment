/*
 * Gia su danh sach duoc cai dat bang mang voi kieu cac truc LIST duoc khai bao
 * nhu sau
 * struct LIST {
 * int data[1000];
 * int length;
 * }
 */

struct LIST {
  int data[1000];
  int length;
};

void removefirst(LIST &l) {
  for (int i = 0; i < l.length - 1; i++) {
    l.data[i] = l.data[i + 1];
  }
  l.length--;
}

void removelast(LIST &l) { l.length--; }

// Nhan xet tinh hieu qua (Thoi gian thuc thi) cua hai ham tren
// removefirst: O(n) voi n la do dai cua danh sach
// removelast: O(1)
// Nhu vay, ham removelast co hieu qua hon ham removefirst
