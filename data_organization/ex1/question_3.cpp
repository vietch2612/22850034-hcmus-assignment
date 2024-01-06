#include <iostream>

int main() {
    int a = 'a'; // a = 97
    // Chuyển giá trị ký tự 'a' sang kiểu số nguyên int.
    // Trong ASCII, ‘a’ có giá trị là 97 nên a = 97.

    int b = (1 < a) + (a < 1000); // b = 2
    // Đây là biểu thức logic nhưng kết quả được chuyển thành kiểu int.
    // Với biểu thức logic, true == 1 và false == 0
    // Nên kết quả sẽ là (1 < 97) + ( 97 < 1000) == true + true == 1 + 1 == 2

    double c = 10.3 + 2;
    // Chuyển giá trị 2 sang kiểu double và cộng với 10.3
    // Kết quả là 12.3

    float d = 10 / 4;
    // Chuyển giá trị 10 sang kiểu float và chia cho 4.
    // Kết quả là 2.5 nhưng vì kiểu dữ liệu của d là float nên kết quả là 2.5f
    std::cout << "d = " << d << std::endl;
    return 0;
}