#include <HighPrecisionCalculator.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
using namespace std;
#define DIVLINE "===================="
int main() {
    cout << DIVLINE << endl;
    cout << "This is high precision calculator version 0.168!" << endl;
    cout << "Enter 'help' to get more information." << endl;
    vector<string> hist;
    while (true) {
        cout << "> ";
        string s;
        getline(cin, s);
        if (s == "quit") {
            cout << "bye" << endl;
            break;
        }
        else if (s == "help") {
            cout << "help               get command illustration" << endl;
            cout << "history            check history formulas" << endl;
            cout << "token              get tokenize expression" << endl;
            cout << "clear              clean screen" << endl;
            cout << "quit               end process" << endl;
        }
        else if (s == "token") {
            string t;
            cout << "Enter expression: ";
            getline(cin, t);
            vector<Token> res = InputTokenizer::split(t);
            for (auto e : res) {
                cout << "\"" << e.name << "\"" << " ";
            }
            cout << endl;
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
            try {
                mpf_class res = HighPrecisionCalculator::calculate(s);
                stringstream ss;
                ss << fixed << setprecision(DEFAULT_PRECISION) << res;
                string ress = ss.str();
                while (ress.size()) {
                    if (ress.back() == '0') {
                        ress.pop_back();
                    }
                    else if (ress.back() == '.') { 
                        ress.pop_back();
                        break;
                    }
                    else break;
                }
                hist.push_back(s + " = " + ress);
                cout << ress << endl;
            }
            catch(const mpf_class& x) {
                cout << "Throw value: " << x << endl;
            }
            catch(const runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
    cout << DIVLINE << endl;
    return 0;
}