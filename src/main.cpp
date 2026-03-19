#include <MathConstants.h>
#include <iostream>
using std::cin, std::cout, std::endl;

int main() {
    long long digits;
    cout << "Enter constant to calculate:\n1) pi\n2) e" << endl;
    int x;
    cin >> x;
    if (x == 1) {
        cout << "Enter calculate digits: ";
        cin >> digits;
        cout << "Calculating " << digits << " digits of pi..." << endl;
        mpf_class pi = MathConstants::compute_pi(digits);
        cout.precision(digits);
        cout << pi << endl;
    }
    else if (x == 2) {
        cout << "Enter calculate digits: ";
        cin >> digits;
        cout << "Calculating " << digits << " digits of e..." << endl;
        mpf_class e = MathConstants::compute_e(digits);
        cout.precision(digits);
        cout << e << endl;
    }
    return 0;
}