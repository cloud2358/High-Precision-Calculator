#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
using namespace boost::multiprecision;

int main() {
    cpp_int a = 1;
    for (int i = 1; i <= 100; i++) {
        a *= i;
    }
    std::cout << a << std::endl;
    system("pause");
    return 0;
}