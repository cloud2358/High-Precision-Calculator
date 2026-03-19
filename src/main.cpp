#include <math_constants.h>
#include <iostream>
#include <functional>
#include <map>
#include <string>

using ComputeFunc = std::function<mpf_class(long long)>;
struct ConstantInfo {
    std::string name;
    ComputeFunc func;
};
std::map<int, ConstantInfo> menu {
    {1, {"pi", MathConstants::ComputePi}}, 
    {2, {"e", MathConstants::ComputeE}}
};

int main() {
    long long digits;
    std::cout << "Enter constant to calculate:" << std::endl;
    for (auto e : menu) {
        std::cout << e.first << ": " << e.second.name << std::endl;
    }
    int x;
    std::cin >> x;
    if (menu.find(x) != menu.end()) {
        std::cout << "Enter calculate digits: ";
        std::cin >> digits;
        std::cout << "Calculating " << digits << " digits of " << menu[x].name << " ..." << std::endl;
        mpf_class result = menu[x].func(digits);
        std::cout.precision(digits);
        std::cout << result << std::endl;
    }
    return 0;
}