#include <iostream>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int nChooseK(int n, int k) {
    if (n < k) {
        return 0;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int nChooseKSmart(int n, int k) {
    if (n < k) {
        return 0;
    }

    int result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= n - k + i;
        result /= i;
    }

    return result;
}

int main() {
    int n = 100000, r = 90000;

    auto startNaive = std::chrono::high_resolution_clock::now();
    nChooseK(n, r);
    auto stopNaive = std::chrono::high_resolution_clock::now();
    auto durationNaive = std::chrono::duration_cast<std::chrono::microseconds>(
        stopNaive - startNaive);

    auto startSmart = std::chrono::high_resolution_clock::now();
    nChooseKSmart(n, r);
    auto stopSmart = std::chrono::high_resolution_clock::now();
    auto durationSmart = std::chrono::duration_cast<std::chrono::microseconds>(
        stopSmart - startSmart);

    std::cout << std::endl;
    std::cout << "nChooseK: " << durationNaive.count() << " microseconds\n";
    std::cout << "nChooseKSmart: " << durationSmart.count()
              << " microseconds\n";

    return 0;
}