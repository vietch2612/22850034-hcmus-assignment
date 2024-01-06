#include <iostream>

int getHcf(int a, int b) {
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int getHcfInArray(int *arr) {
    int size = sizeof(&arr) / sizeof(arr[0]);
    int result = 0;
    for (int i = 0; i <= size; i++) {
        result = getHcf(result, arr[i]);
    }

    return result;
}

void printArray(int *arr) {
    int size = sizeof(&arr) / sizeof(arr[0]);
    for (int i = 0; i <= size; i++) {
        std::cout << arr[i] << ", ";
    }
}

int main() {
    int arr[] = {12, 18, 24}; // 6
    printArray(arr);
    std::cout << " HCF: " << getHcfInArray(arr) << std::endl;

    int arr2[] = {36, 48, 60}; // 12
    printArray(arr2);
    std::cout << " HCF: " << getHcfInArray(arr2) << std::endl;

    int arr3[] = {15, 25, 35}; // 5
    printArray(arr3);
    std::cout << " HCF: " << getHcfInArray(arr3) << std::endl;

    return 0;
}
