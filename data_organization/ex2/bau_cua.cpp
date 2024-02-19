#include <iostream>

using namespace std;

#define DUNG 0
#define RUNG 7
#define TOTAL 6

string ten[TOTAL] = {"Tom", "Cua", "Bau", "Ca", "Ga", "Nai"};

void xuat(int cuoc[]) {
  int tongCuoc = 0;

  for (int i = 0; i < TOTAL; i++) tongCuoc += cuoc[i];
  if (tongCuoc == 0) {
    cout << "Ban chua dat cuoc!" << endl;
  } else {
    cout << "Ban dang dat: ";
    for (int i = 0; i < TOTAL; i++)
      if (cuoc[i] > 0) cout << ten[i] << ": " << cuoc[i] << "; ";
    cout << endl;
  }

  cout << "Ban muon (0-Dung, 1-Tom, 2-Cua, 3-Bau, 4-Ca, 5-Ga, 6-Nai, 7-Rung): ";
}

void xuatTongCuoc(int cuoc[]) {
  int kq = 0;
  for (int i = 0; i < TOTAL; i++) kq += cuoc[i];
  cout << "Tong cuoc: " << kq << endl;
}

void rung(int kqRung[]) {
  cout << "KQ rung: ";
  for (int i = 0; i < 3; i++) {
    int t = rand() % 6;
    kqRung[i] = t;
    cout << ten[t] << " ";
  }
  cout << endl;
}

void xuatKqRung(int cuoc[], int kqRung[]) {
  int result = 0;
  for (int i = 0; i < 3; i++) {
    result += cuoc[kqRung[i]];
  }
  for (int i = 0; i < TOTAL; i++) cuoc[i] = 0;

  cout << "Ban con lai " << result << endl;
}

int main() {
  int cmd;
  int cuoc[TOTAL] = {0};
  int kqRung[3] = {0};

  srand(time(0));
  while (1) {
    xuat(cuoc);
    cin >> cmd;

    if (cmd == DUNG) {
      cout << "Chuc mung nam moi!" << endl;
      return 0;
    }

    if (cmd >= 1 && cmd <= 6) {
      cout << "Ban muon dat " << ten[cmd - 1] << " bao nhieu tien? ";
      cin >> cuoc[cmd - 1];
    }

    if (cmd == RUNG) {
      xuatTongCuoc(cuoc);
      rung(kqRung);
      xuatKqRung(cuoc, kqRung);
      return 0;
    }
  }

  return 0;
}
