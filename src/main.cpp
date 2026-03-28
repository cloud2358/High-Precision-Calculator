#include <high_precision_calculator.h>
#include <iostream>
using namespace std;
#define DIVLINE "===================="
int main() {
    cout << DIVLINE << endl;
    cout << "This is high precision calculator version 0.162!" << endl;
    cout << "Press 'q' to quit calculator." << endl;
    while (true) {
        cout << DIVLINE << endl;
        cout << "Enter input expression: " << endl;
        string s;
        std::getline(cin, s);
        if (s[0] == 'q') break;
        cout << HighPrecisionCalculator::calculate(s) << endl;
    }
    cout << DIVLINE << endl;
    return 0;
}