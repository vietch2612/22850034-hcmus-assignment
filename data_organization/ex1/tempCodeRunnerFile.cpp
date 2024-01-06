#include <cmath>
#include <iostream>

double getAbsoluteValue(double x) {
    if (x < 0)
        return -x;
    return x;
}

double myCbrt(double y) {
    double mid, l, r;
    const double EPS = 0.0000001;

    if (y > 1)
        r = y;
    else
        r = 1;
    l = 0;

    do {
        mid = (l + r) / 2;
        if (mid * mid * mid > y)
            r = mid;
        else
            l = mid;
    } while (getAbsoluteValue(mid * mid * mid - y) > EPS);

    return mid;
}

int main() {
    double x = 3;

    std::cout << std::endl;
    std::cout << "mySqrt(" << x << ") = " << myCbrt(x) << std::endl;
    std::cout << "std::sqrt(" << x << ") = " << std::cbrt(x) << std::endl;

    return 0;
}