#include <MathConstants.h>
#include <iostream>

using std::cin, std::cout, std::endl;

// Get first n equivalent digits of x and y.
size_t get_equal_digits(mpf_class x, mpf_class y) {
    size_t res = 0;
    /*
    Pseudo code:
        while res < min(x.length, y.length)
            if x[res] == y[res]
                res = res + 1;
            else
                break
    */
    return res;
}

int main() {
    size_t digits;
    cout << "Digits to check: ";
    cin >> digits;
    /*
        Pi accuracy: equal digits / digits
        e accuracy: ...
    */
    return 0;
}