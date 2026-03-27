#include <high_precision_calculator.h>
#include <iostream>
using namespace std;

int main() {
    cout << "Enter input expression: " << endl;
    string s;
    cin >> s;
    cout << HighPrecisionCalculator::calculate(s);
    return 0;
}