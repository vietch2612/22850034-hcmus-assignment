#include <iostream>

int main() {
  // Input 2D array
  int m, n;
  std::cout << "So hang: ";
  std::cin >> m;
  std::cout << "So cot: ";
  std::cin >> n;
  int a[m][n];
  std::cout << "Bat dau nhap cac phan tu cua mang." << std::endl;
  for (int i = 0; i < m; i++) {
    std::cout << "a[" << i << "][?]: ";
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
  }

  // Start finding saddle points
  // Create variables to locations and number of points
  int saddlePointsCount = 0;
  int saddlePoints[m][n];
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) saddlePoints[i][j] = 0;

  // Loop through each row
  for (int i = 0; i < m; i++) {
    int min = a[i][0];  // init min = first element
    int minCol = 0;     // min column index

    // At row i, go through from left to right to find the minimum col
    for (int j = 1; j < n; j++) {
      if (a[i][j] < min) {
        min = a[i][j];
        minCol = j;
      }
    }

    bool isSaddlePoint = true;  // assume it is true then validate it

    // Loop through each element in column minCol from 0 to m
    // If it is not the highest value, break
    for (int k = 0; k < m; k++) {
      if (a[k][minCol] > min) {
        isSaddlePoint = false;
        break;
      }
    }

    // Save the result
    if (isSaddlePoint) {
      saddlePoints[i][minCol] = 1;  // let assume 1 means true
      saddlePointsCount++;
    }
  }

  std::cout << "Hien thi lai ma tran 2D: " << std::endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  // Output saddle points
  std::cout << "Cac diem yen ngua cua mang: " << std::endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (saddlePoints[i][j] == 1) {
        std::cout << "Diem yen ngua: a[" << i << "," << j << "]: " << a[i][j]
                  << std::endl;
      }
    }
  }

  std::cout << "So luong diem yen ngua: " << saddlePointsCount << std::endl;
  return 0;
}
