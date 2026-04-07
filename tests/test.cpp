#include <HighPrecisionCalculator.h>
#include <iostream>
#include <conio.h>
using namespace std;
#define DIVLINE "===================="
int main() {
    cout << DIVLINE << endl;
    cout << "This is high precision calculator version 0.162!" << endl;
    cout << "Enter 'help' to get more information." << endl;
    vector<string> hist;
    while (true) {
        cout << "> ";
        string s;
        std::getline(cin, s);
        if (s == "quit") {
            cout << "bye" << endl;
            break;
        }
        else if (s == "help") {
            cout << "help               get command illustration" << endl;
            cout << "history            check history formulas" << endl;
            cout << "clear              clean screen" << endl;
            cout << "quit               end process" << endl;
        }
        else if (s == "history") {
            if (hist.empty()) {
                cout << "History not found" << endl;
                continue;
            }
            for (auto e : hist) {
                cout << e << endl;
            }
        }
        else if (s == "clear") {
            cout << "\x1B[2J\x1B[H";
        }
        else {
            auto res = HighPrecisionCalculator::calculate(s);
            
            mp_exp_t exp;
            string a = res.get_str(exp, 10, 8);
            
            std::string result;
            if (exp <= 0) {
                result = "0." + std::string(-exp, '0') + a;
            }
            else if ((size_t)exp >= a.size()) {
                result = a + std::string(exp - a.size(), '0');
            }
            else {
                result = a.substr(0, exp) + "." + a.substr(exp);
            }
            hist.push_back(s + " = " + result);
            cout << result << endl;
        }
    }
    cout << DIVLINE << endl;
    return 0;
}