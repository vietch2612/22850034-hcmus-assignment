#include <cmath>
#include <iostream>

double factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

double sin(double x) {
    double result = 0;
    for (int i = 0; i < 10; ++i) {
        result += pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
    }

    return result;
}

int main() {
    double x = 0.5;

    std::cout << std::endl;
    std::cout << "sin(" << x << ") = " << sin(x) << std::endl;
    std::cout << "std::sin(" << x << ") = " << std::sin(x) << std::endl;

    return 0;
}