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
                vector<mpf_class> result = HighPrecisionCalculator::calculate(s);
                string ans;
                for (size_t i = 0; i < result.size(); i++) {
                    auto res = result[i];
                    stringstream ss;
                    ss << fixed << setprecision(DEFAULT_PRECISION) << res;
                    string res_str = ss.str();
                    while (res_str.size()) {
                        if (res_str.back() == '0') {
                            res_str.pop_back();
                        }
                        else if (res_str.back() == '.') { 
                            res_str.pop_back();  
                            break;
                        }
                        else break;
                    }
                    ans += res_str;
                    if (i + 1 < result.size()) ans += ", ";
                }
                hist.push_back(s + " = " + ans);
                cout << ans << endl;
            }
            catch(const mpf_class& x) {
                cout << "Throw value: " << x << endl;
            }
            catch(const mpz_class& x) {
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